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
#ifdef __linux__
#include <sys/epoll.h>
#elif defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
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

char *parse_body(char *request_buf)
{
	char *start = strstr(request_buf, "\r\n\r\n");
	if (start == NULL) {
		return NULL;
	}
	return start + 4;
}

void parse_path(char *request_buf, char *path_out, char *method_out)
{
	char version[16];

	// Parse the first line: METHOD PATH VERSION
	sscanf(request_buf, "%7s %1023s %15s", method_out, path_out, version);

	printf("Method: %s\n", method_out);
	printf("Path: %s\n", path_out);
	printf("Version: %s\n", version);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);

	char *iflank_path = "iflank";
	char *iflank_name = "iflank";
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

	int to_iflank_pipe_rw[2], from_iflank_pipe_rw[2];
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

	int flags = fcntl(from_iflank_pipe_rw[0], F_GETFL, 0);
	fcntl(from_iflank_pipe_rw[0], F_SETFL, flags | O_NONBLOCK);

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
	printf("Echo server listening on port %d...\n", PORT);

#ifdef __linux__
	int ep = epoll_create1(0);
	if (ep == -1) {
		perror("epoll_create1");
		exit(1);
	}

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = from_iflank_pipe_rw[0];
	if (epoll_ctl(ep, EPOLL_CTL_ADD, from_iflank_pipe_rw[0], &ev) == -1) {
		perror("epoll_ctl");
		exit(1);
	}
#elif defined(__APPLE__) || defined(__FreeBSD__)
	int kq = kqueue();
	struct kevent ev;
	EV_SET(&ev, from_iflank_pipe_rw[0], EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &ev, 1, NULL, 0, NULL);	// register
#else
#error "Unsupported platform"
#endif

    int active_client_fd;
	while (1) {
		// Accept a client
		// Creates a new FD whose file description points at send/receive buffers in kernel space
		client_fd = accept(server_fd, NULL, NULL);
		if (client_fd < 0) {
			perror("accept");
			continue;
		}
		// read() returns 0 at EOF, when the other side closes the connection
		while ((http_bytes_read =
			read(client_fd, buffer, BUF_SIZE - 1)) > 0) {
			// send input to iflank
			buffer[http_bytes_read] = '\0';
			char *body = parse_body(buffer);
			char path[1024];
			char method[8];
			parse_path(buffer, path, method);
			// printf("path: %s\n", path);
			if (strcmp(path, "/iflank") == 0
			    && strcmp(method, "POST") == 0) {
				printf("about to write\n");
				write(to_iflank_pipe_rw[1], body,
				      buffer + http_bytes_read - body);
				printf("done writing\n");
				char header[] = "HTTP/1.1 200 OK\r\n"
				    "Content-Length: 0\r\n\r\n";
				write(client_fd, header, sizeof(header) - 1);
			} else if (strcmp(path, "/iflank") == 0
				   && strcmp(method, "GET") == 0) {
				printf("about to non-block read\n");
                active_client_fd = client_fd;

#ifdef __linux__
				struct epoll_event events[1];
				int n = epoll_wait(ep, events, 1, -1);	// -1 = block indefinitely
#elif defined(__APPLE__) || defined(__FreeBSD__)
				struct kevent events[1];
				int n = kevent(kq, NULL, 0, events, 1, NULL);	// NULL timeout = block
#else
#error "Unsupported platform"
#endif

				int iflank_bytes_read =
				    read(from_iflank_pipe_rw[0], buffer,
					 BUF_SIZE - 1);
				printf("iflank bytes read: %d / %d\n",
				       iflank_bytes_read, BUF_SIZE - 1);
				printf("buffer:\n%s\n", buffer);
				char header[256];
				int header_len;
				if (iflank_bytes_read == -1) {
					if (errno == EAGAIN
					    || errno == EWOULDBLOCK) {
						printf("No input available\n");
						header_len =
						    snprintf(header,
							     sizeof(header),
							     "HTTP/1.1 200 OK\r\n"
							     "Content-Type: text/plain\r\n"
							     "Content-Length: 0\r\n\r\n");
					} else {
						header_len =
						    snprintf(header,
							     sizeof(header),
							     "HTTP/1.1 500 Internal Server Error\r\n"
							     "Content-Type: text/plain\r\n"
							     "Content-Length: 0\r\n\r\n");
						perror("read");
					}
				} else {
					header_len =
					    snprintf(header, sizeof(header),
						     "HTTP/1.1 200 OK\r\n"
						     "Content-Type: text/plain\r\n"
						     "Content-Length: %d\r\n\r\n",
						     iflank_bytes_read);
				}
				write(active_client_fd, header, header_len);	// forward to client
				if (iflank_bytes_read != -1) {
					write(active_client_fd, buffer, iflank_bytes_read);	// forward to client
				}
			} else if (strcmp(path, "/") == 0) {
				const char *index_html_path = NULL;

				if (access("./index.html", F_OK) == 0) {
					index_html_path = "./index.html";
				} else
				    if (access
					("/usr/share/flank/index.html",
					 F_OK) == 0) {
					index_html_path =
					    "/usr/share/flank/index.html";
				} else {
					fprintf(stderr,
						"index.html not found\n");
					return 1;
				}
				int fd = open(index_html_path, O_RDONLY);
				struct stat st;
				fstat(fd, &st);
				off_t filesize = st.st_size;
				char header[256];
				int header_len;
				header_len = snprintf(header, sizeof(header),
						      "HTTP/1.1 200 OK\r\n"
						      "Content-Type: text/html\r\n"
						      "Content-Length: %lld\r\n"
						      "\r\n",
						      (long long)filesize);
				write(client_fd, header, header_len);	// forward to client
				ssize_t n;
				while ((n =
					read(fd, buffer, sizeof(buffer))) > 0) {
					write(client_fd, buffer, n);
				}
				close(fd);
			} else {
				if (access(path, F_OK) == 0) {
					int fd = open(path, O_RDONLY);
					struct stat st;
					fstat(fd, &st);
					off_t filesize = st.st_size;
					char header[256];
					int header_len;
					header_len =
					    snprintf(header, sizeof(header),
						     "HTTP/1.1 200 OK\r\n"
						     "Content-Type: text/html\r\n"
						     "Content-Length: %lld\r\n"
						     "\r\n",
						     (long long)filesize);
					write(client_fd, header, header_len);	// forward to client
					ssize_t n;
					while ((n =
						read(fd, buffer,
						     sizeof(buffer))) > 0) {
						write(client_fd, buffer, n);
					}
					close(fd);

				} else {
					printf("path not supported: %s\n",
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
			printf("request done\n");
		}

		close(client_fd);
	}

	close(server_fd);
	return 0;
}
