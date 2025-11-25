#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

#ifdef __linux__
#include <sys/epoll.h>
#elif defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/types.h>
#include <sys/event.h>
#else
#error "Unsupported platform"
#endif

#define BUF_SIZE 600000

int server_fd;			// used in signal handlers
int PORT = 8083;		// doesn't need to be here unless I refactor and don't want to pass around

void sigint_handler(int sig)
{
	close(server_fd);	// free the listening socket
	exit(0);
}

static char ts_buf[32];		// "YYYY‑MM‑DD HH:MM:SS"

/* Return a static timestamp string, e.g. "2025-10-06 14:23:45" */
static const char *timestamp(void)
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(ts_buf, sizeof(ts_buf), "%Y-%m-%dT%H:%M:%S", t);
	return ts_buf;
}

int tsprintf(const char *fmt, ...)
{
	va_list ap;
	int n;

	/* Print the timestamp first */
	fprintf(stdout, "[%s] ", timestamp());

	/* Then the user‑supplied formatted text */
	va_start(ap, fmt);
	n = vfprintf(stdout, fmt, ap);
	va_end(ap);

	return n;
}

char *parse_body(char *request_buf)
{
	char *start = strstr(request_buf, "\r\n\r\n");
	if (start == NULL) {
		return NULL;
	}
	return start + 4;
}

void parse_sid(char *request_buf, char *sid_out)
{
	char header[] = "X-Session-ID:";
	char *header_ptr = strstr(request_buf, header);
	if (header_ptr == NULL) {
		sid_out[0] = '\0';
		return;
	}
	header_ptr += sizeof(header) - 1;
	while (*header_ptr == ' ') {
		header_ptr += 1;
	}
	strncpy(sid_out, header_ptr, 11);
	sid_out[11] = '\0';
}

struct session {
	char sid[12];
	int r_fd;
	int w_fd;
	int long_poll_req_fd;
};
int find_session(struct session *sessions, int n_sessions, char *sid)
{
	for (int i = 0; i < n_sessions; i++) {
		if (sessions[i].sid[0] != '\0'
		    && strcmp(sessions[i].sid, sid) == 0) {
			return i;
		}
	}
	return -1;
}

void parse_path(char *request_buf, char *path_out, char *method_out)
{
	char version[16];

	// sscanf params have one less character than fixed arrays
	// (e.g. %7s versus method[8]) to leave room for null terminator)
	sscanf(request_buf, "%7s %1023s %15s", method_out, path_out, version);

	tsprintf("%s %s %s\n", method_out, path_out, version);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);

	char *iflank_path = "iflank";
	char *iflank_name = "iflank";
	struct session sessions[64] = { 0 };
	if (strstr(argv[0], "fsl") != NULL) {
		PORT = 8084;
	}
	for (int i = 1; i + 1 < argc; ++i) {
		if (strcmp(argv[i], "--iflank-path") == 0) {
			iflank_path = argv[i + 1];
			char *last_slash = strrchr(iflank_path, '/');
			if (last_slash > 0) {
				iflank_name = last_slash + 1;
			} else {
				iflank_name = last_slash;
			}
			break;
		}
	}
	int client_fd;
	struct sockaddr_in addr;
	char buffer[BUF_SIZE];
	int http_bytes_read;

	// Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);	// AF_NET = Address Family IPv4 / SOCK_STREAM = Socket Type TCP / 0 = Protocol = Let OS decide
	if (server_fd < 0) {
		perror("socket");
		exit(1);
	}
	// Prevents port from being tied up after exit
	int opt = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Bind
	// This is kernel bookkeeping
	// The file description has been set up and hooked up to user land
	// It will be used to bind/listen/accept
	// This just tells the kernel's TCP stack which port to listen on
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}
	// Listen - Actually start listening for calls
	if (listen(server_fd, 5) < 0) {
		perror("listen");
		exit(1);
	}
	tsprintf("Server listening on port %d...\n", PORT);

	// Create Queue
#ifdef __linux__
	int ep = epoll_create1(0);
	if (ep == -1) {
		perror("epoll_create1");
		exit(1);
	}
#elif defined(__APPLE__) || defined(__FreeBSD__)
	int kq = kqueue();
#else
#error "Unsupported platform"
#endif

	// Register the server FD
#ifdef __linux__
	struct epoll_event req_ev;
	req_ev.events = EPOLLIN;
	req_ev.data.fd = server_fd;
	if (epoll_ctl(ep, EPOLL_CTL_ADD, server_fd, &req_ev) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
#elif defined(__APPLE__) || defined(__FreeBSD__)
	struct kevent req_ev;
	EV_SET(&req_ev, server_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &req_ev, 1, NULL, 0, NULL);	// register
#else
#error "Unsupported platform"
#endif

	while (1) {
#ifdef __linux__
		struct epoll_event events[64];
		int n = epoll_wait(ep, events, 64, -1);	// -1 = block indefinitely
#elif defined(__APPLE__) || defined(__FreeBSD__)
		struct kevent events[64];
		int n = kevent(kq, NULL, 0, events, 64, NULL);	// NULL timeout = block
#else
#error "Unsupported platform"
#endif

		for (int i = 0; i < n; i++) {
#ifdef __linux__
			int event_fd = events[i].data.fd;
#elif defined(__APPLE__) || defined(__FreeBSD__)
			int event_fd = events[i].ident;
#else
#error "Unsupported platform"
#endif

			struct session sesh;
			if (event_fd == server_fd) {
				client_fd = accept(event_fd, NULL, NULL);
				if (client_fd < 0) {
					perror("accept");
					continue;
				}
				// Leave an extra character so that 
				// string can be null terminated
				http_bytes_read =
				    read(client_fd, buffer, BUF_SIZE - 1);
				// send input to iflank
				buffer[http_bytes_read] = '\0';
				char *body = parse_body(buffer);
				char path[1024];
				char method[8];
				char sid[12];
				parse_path(buffer, path, method);
				parse_sid(buffer, sid);

				if (strcmp(path, "/iflank") == 0
				    && strcmp(sid, "") != 0) {
					int s_idx =
					    find_session(sessions, 64, sid);
					if (s_idx >= 0) {
						sesh = sessions[s_idx];
						printf
						    ("Session Found: %s %d %d\n",
						     sesh.sid, sesh.r_fd,
						     sesh.w_fd);
					} else {
						printf
						    ("Session NOT found: %s\n",
						     sid);
						int j = 0;
						for (; j < 64; j++) {
							if (sessions[j].
							    sid[0] == '\0') {
								printf
								    ("break sid %d: %s\n",
								     j,
								     sessions
								     [j].sid);
								break;
							}
						}
						printf("session j :%d\n", j);
						int to_iflank_pipe_rw[2],
						    from_iflank_pipe_rw[2];
						pid_t pid;

						pipe(to_iflank_pipe_rw);	// creates pipe, fills `to_iflank_pipe_rw[0]` with read FD and `to_iflank_pipe_rw[1]` with write FD
						pipe(from_iflank_pipe_rw);	// parent reads from child stdout

						pid = fork();
						if (pid == 0) {
							// Child process 
							dup2(to_iflank_pipe_rw[0], STDIN_FILENO);	// in file descriptor table,
							// point 0 at whatever file description 
							// is specified by the FD in to_iflank_pipe_rw[0]
							dup2(from_iflank_pipe_rw[1], STDOUT_FILENO);	// in file descriptor table,
							// point 1 at whatever FD is write end of pipe
							close(to_iflank_pipe_rw[1]);	// close the "write" end of the "to" pipe (it's for the parent)
							close(from_iflank_pipe_rw[0]);	// close the "read" end of the "from" pipe (it's for the parent)
							execlp(iflank_path, iflank_name, "--http-mode", NULL);	// filename, argv[0] the name the program sees itself as, end of arg list
							perror("execlp");
							exit(1);
						} else {
							// Parent process
							close(to_iflank_pipe_rw[0]);	// close the "read" end of the "to" pipe (it's for the child)
							close(from_iflank_pipe_rw[1]);	// close the "write" end of the "from" pipe (it's for the child) 
						}

						int flags =
						    fcntl(from_iflank_pipe_rw
							  [0],
							  F_GETFL, 0);
						fcntl(from_iflank_pipe_rw[0],
						      F_SETFL,
						      flags | O_NONBLOCK);
						strcpy(sessions[j].sid, sid);
						printf
						    ("sessions[j].sid : %d : %s\n",
						     j, sessions[j].sid);
						sessions[j].r_fd =
						    from_iflank_pipe_rw[0];
						sessions[j].w_fd =
						    to_iflank_pipe_rw[1];
						sessions[j].long_poll_req_fd =
						    -1;
						sesh = sessions[j];
						printf("session created\n");
					}
				}
				if (strcmp(path, "/iflank") == 0
				    && strcmp(method, "POST") == 0) {
					printf("sesh.w_fd: %d\n", sesh.w_fd);
					write(sesh.w_fd, body,
					      buffer + http_bytes_read - body);
					char header[] = "HTTP/1.1 200 OK\r\n"
					    "Content-Length: 0\r\n\r\n";
					write(client_fd, header,
					      sizeof(header) - 1);
					tsprintf("%s\n", body);
				} else if (strcmp(path, "/iflank") == 0
					   && strcmp(method, "GET") == 0) {
					sesh.long_poll_req_fd = client_fd;
					// Register the read end of the iflank pipe
#ifdef __linux__
					struct epoll_event iflank_ev;
					iflank_ev.events = EPOLLIN;
					iflank_ev.data.fd = sesh.r_fd;
					if (epoll_ctl
					    (ep, EPOLL_CTL_ADD,
					     sesh.r_fd, &iflank_ev) == -1) {
						perror("epoll_ctl");
						exit(1);
					}
#elif defined(__APPLE__) || defined(__FreeBSD__)
					struct kevent iflank_ev;
					EV_SET(&iflank_ev,
					       sesh.r_fd,
					       EVFILT_READ, EV_ADD, 0, 0, NULL);
					kevent(kq, &iflank_ev, 1, NULL, 0, NULL);	// register
#else
#error "Unsupported platform"
#endif
					continue;
				} else if (strcmp(path, "/") == 0) {
					const char *index_html_path = NULL;

					int found = 0;
					if (access("./index.html", F_OK) == 0) {
						index_html_path =
						    "./index.html";
						found = 1;
					} else if (access
						   ("/usr/share/flank/index.html",
						    F_OK) == 0) {
						index_html_path =
						    "/usr/share/flank/index.html";
						found = 1;
					} else {
						tsprintf
						    ("ERROR: index.html not found\n");
					}
					if (found) {
						if (sesh.long_poll_req_fd != -1) {
							close
							    (sesh.
							     long_poll_req_fd);
							sesh.long_poll_req_fd =
							    -1;

							// Clear the iflank pipe from the queue until a new GET comes in
#ifdef __linux__
							epoll_ctl(ep,
								  EPOLL_CTL_DEL,
								  sesh.r_fd,
								  NULL);
#elif defined(__APPLE__) || defined(__FreeBSD__)
							struct kevent ev;
							EV_SET(&ev,
							       sesh.r_fd,
							       EVFILT_READ,
							       EV_DELETE, 0, 0,
							       NULL);
							kevent(kq, &ev, 1, NULL,
							       0, NULL);
#else
#error "Unsupported platform"
#endif
						}
						int fd = open(index_html_path,
							      O_RDONLY);
						struct stat st;
						fstat(fd, &st);
						off_t filesize = st.st_size;
						char header[256];
						int header_len;
						header_len =
						    snprintf(header,
							     sizeof(header),
							     "HTTP/1.1 200 OK\r\n"
							     "Content-Type: text/html\r\n"
							     "Content-Length: %lld\r\n"
							     "\r\n", (long long)
							     filesize);
						write(client_fd, header, header_len);	// forward to client
						ssize_t n;
						while ((n =
							read(fd, buffer,
							     BUF_SIZE)) > 0) {
							write(client_fd, buffer,
							      n);
							tsprintf("/ n %d\n", n);
						}
						close(fd);
					} else {
						char header[] =
						    "HTTP/1.1 404 Not Found\r\n"
						    "Content-Length: 0\r\n\r\n";
						write(client_fd, header,
						      sizeof(header) - 1);
					}
				} else {
					if (access(path, F_OK) == 0) {
						int fd = open(path, O_RDONLY);
						struct stat st;
						fstat(fd, &st);
						off_t filesize = st.st_size;
						char header[256];
						int header_len;
						header_len =
						    snprintf(header,
							     sizeof(header),
							     "HTTP/1.1 200 OK\r\n"
							     "Content-Type: text/html\r\n"
							     "Content-Length: %lld\r\n"
							     "\r\n", (long long)
							     filesize);
						write(client_fd, header, header_len);	// forward to client
						ssize_t n;
						while ((n =
							read(fd, buffer,
							     BUF_SIZE)) > 0) {
							write(client_fd, buffer,
							      n);
							tsprintf("path %d\n",
								 n);
						}
						close(fd);

					} else {
						tsprintf
						    ("ERROR: path not supported: %s\n",
						     path);
						// char header[256];
						// int header_len;
						char header[] =
						    "HTTP/1.1 404 Not Found\r\n"
						    "Content-Length: 0\r\n\r\n";
						write(client_fd, header,
						      sizeof(header) - 1);
					}
				}
				close(client_fd);
			} else {	// event_fd != server_fd
				int iflank_bytes_read =
				    read(event_fd, buffer, BUF_SIZE);
				char header[256];
				int header_len;
				if (iflank_bytes_read == -1) {
					header_len =
					    snprintf(header,
						     sizeof(header),
						     "HTTP/1.1 200 OK\r\n"
						     "Content-Type: text/plain\r\n"
						     "Content-Length: 0\r\n\r\n");
					write(sesh.long_poll_req_fd, header, header_len);	// forward to client
				} else {
					header_len =
					    snprintf(header, sizeof(header),
						     "HTTP/1.1 200 OK\r\n"
						     "Content-Type: text/plain\r\n"
						     "Content-Length: %d\r\n\r\n",
						     iflank_bytes_read);
					write(sesh.long_poll_req_fd, header, header_len);	// forward to client
					int n = write(sesh.long_poll_req_fd, buffer, iflank_bytes_read);	// forward to client
					tsprintf("get %d\n", iflank_bytes_read);
				}
				close(sesh.long_poll_req_fd);
				sesh.long_poll_req_fd = -1;

				// Clear the iflank pipe from the queue until a new GET comes in
#ifdef __linux__
				epoll_ctl(ep, EPOLL_CTL_DEL, sesh.r_fd, NULL);
#elif defined(__APPLE__) || defined(__FreeBSD__)
				struct kevent ev;
				EV_SET(&ev, sesh.r_fd, EVFILT_READ,
				       EV_DELETE, 0, 0, NULL);
				kevent(kq, &ev, 1, NULL, 0, NULL);
#else
#error "Unsupported platform"
#endif
			}
		}
	}

	close(server_fd);
	return 0;
}
