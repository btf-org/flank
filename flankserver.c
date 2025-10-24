#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

#define BUF_SIZE 4096

int server_fd;			// used in signal handlers
int PORT = 8083;		// doesn't need to be here unless I refactor and don't want to pass around

void sigint_handler(int sig) {
     close(server_fd);		// free the listening socket
     exit(0);
}

char *parse_body(char *request_buf) {
     char *start = strstr(request_buf, "\r\n\r\n");
     if (start == NULL) {
	  return NULL;
     }
     return start + 4;
}

void parse_path(char *request_buf, char *path_out, char *method_out) {
     char version[16];

     // Parse the first line: METHOD PATH VERSION
     sscanf(request_buf, "%7s %1023s %15s", method_out, path_out, version);

     printf("Method: %s\n", method_out);
     printf("Path: %s\n", path_out);
     printf("Version: %s\n", version);
}

int main(int argc, char *argv[]) {
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

     while (1) {
	  // Accept a client
	  // Creates a new FD whose file description points at send/receive buffers in kernel space
	  client_fd = accept(server_fd, NULL, NULL);
	  if (client_fd < 0) {
	       perror("accept");
	       continue;
	  }

	  int iflank_bytes_read = 0;
	  // while ((iflank_bytes_read = read(from_iflank_pipe_rw[0], buffer, BUF_SIZE)) > 0) {
	  //      write(client_fd, buffer, iflank_bytes_read); // forward to client
	  //      printf("iflank_bytes_read < BUF_SIZE? %d <? %d \n", iflank_bytes_read, BUF_SIZE);
	  //      if (iflank_bytes_read < BUF_SIZE){
	  //              printf("break\n");
	  //              break; // stop if child has no more data
	  //      }
	  // }
	  // read() returns 0 at EOF, when the other side closes the connection
	  while ((http_bytes_read = read(client_fd, buffer, BUF_SIZE - 1)) > 0) {
	       // send input to iflank
	       buffer[http_bytes_read] = '\0';
	       printf("HTTP Input: %s\n", buffer);
	       printf("HTTP Bytes read: %d\n", http_bytes_read);
	       //for (int i = 0; i < http_bytes_read; i++) {
	       //  printf("%d ", (unsigned char)buffer[i]);
	       //}
	       printf("\n");
	       char *body = parse_body(buffer);
	       char path[1024];
	       char method[8];
	       parse_path(buffer, path, method);
	       printf("path: %s\n", path);
	       if (strcmp(path, "/iflank") == 0) {
		    printf("remainder: %s\n", body);
		    printf("about to write\n");
		    write(to_iflank_pipe_rw[1], body,
			  buffer + http_bytes_read - body);
		    printf("just wrote: %s\n", body);

		    // flush if using FILE*, otherwise ensure child gets data
		    // fflush(iflank_stdin); // if you wrap pipe with fdopen

		    // read response from iflank
		    // int iflank_bytes_read;
		    char *buf_head = buffer;
		    while ((iflank_bytes_read +=
			    read(from_iflank_pipe_rw[0], buf_head,
				 BUF_SIZE - 1)) > 0) {
			 buf_head = &buffer[iflank_bytes_read];
			 // buffer[iflank_bytes_read] = '\0';
			 printf("iflank bytes read: %d\n", iflank_bytes_read);
			 // printf("iflank's Output: %s\n", buffer);
			 for (int i = 0; i < iflank_bytes_read; i++) {
			      printf("%d ", (unsigned char)buffer[i]);
			 }
			 for (int i = 0; i < iflank_bytes_read; i++) {
			      printf("%c ", (unsigned char)buffer[i]);
			 }
			 printf("\n");
			 //if (iflank_bytes_read < BUF_SIZE) {
			 if (buffer[iflank_bytes_read - 1] == '\0') {
			      printf("Full message %s\n", buffer);
			      char header[256];
			      int header_len;
			      header_len =
				  snprintf(header, sizeof(header),
					   "HTTP/1.1 200 OK\r\n"
					   "Content-Type: text/plain\r\n"
					   "Content-Length: %d\r\n" "\r\n",
					   iflank_bytes_read);
			      write(client_fd, header, header_len);	// forward to client
			      write(client_fd, buffer, iflank_bytes_read);	// forward to client
			      iflank_bytes_read = 0;
			      break;	// stop if child has no more data
			 }
		    }
	       } else if (strcmp(path, "/") == 0) {
		    const char *index_html_path = NULL;

		    if (access("./index.html", F_OK) == 0) {
			 index_html_path = "./index.html";
		    } else if (access("/usr/share/flank/index.html", F_OK) == 0) {
			 index_html_path = "/usr/share/flank/index.html";
		    } else {
			 fprintf(stderr, "index.html not found\n");
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
					  "\r\n", (long long)filesize);
		    write(client_fd, header, header_len);	// forward to client
		    ssize_t n;
		    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
			 write(client_fd, buffer, n);
		    }
		    close(fd);
	       } else {
		    printf("path not supported: %s\n", path);
		    // char header[256];
		    // int header_len;
		    char header[] = "HTTP/1.1 404 Not Found\r\n"
			"Content-Length: 0\r\n\r\n";
		    write(client_fd, header, sizeof(header) - 1);
	       }
	  }

	  close(client_fd);
     }

     close(server_fd);
     return 0;
}
