#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 8083
#define BUF_SIZE 4096

int server_fd;

void sigint_handler(int sig) {
     close(server_fd);		// free the listening socket
     exit(0);
}

char *parse_body(char *request_buf) {
     char *start = strstr(request_buf, "\r\n\r\n");
     if (start == 0) {
	  return NULL;
     }
     return start + 4;
}

void parse_path(char *request_buf, char *path_out) {
     char method[8];
     char path[1024];
     char version[16];

     // Parse the first line: METHOD PATH VERSION
     sscanf(request_buf, "%7s %1023s %15s", method, path_out, version);

     printf("Method: %s\n", method);
     printf("Path: %s\n", path_out);
     printf("Version: %s\n", version);
}

int main(int argc, char *argv[]) {
     signal(SIGINT, sigint_handler);
     signal(SIGTERM, sigint_handler);

     char *iflank_path = "iflank";
     char *iflank_name = "iflank";
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
     int bytes_read;

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
	  execlp(iflank_path, iflank_name, NULL);	// filename, argv[0] the name the program sees itself as, end of arg list
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

	  int out_bytes;
	  // while ((out_bytes = read(from_iflank_pipe_rw[0], buffer, BUF_SIZE)) > 0) {
	  //      write(client_fd, buffer, out_bytes); // forward to client
	  //      printf("out_bytes < BUF_SIZE? %d <? %d \n", out_bytes, BUF_SIZE);
	  //      if (out_bytes < BUF_SIZE){
	  //              printf("break\n");
	  //              break; // stop if child has no more data
	  //      }
	  // }
	  // read() returns 0 at EOF, when the other side closes the connection
	  while ((bytes_read = read(client_fd, buffer, BUF_SIZE)) > 0) {
	       // send input to iflank
	       buffer[bytes_read] = '\0';
	       printf("Input: %s\n", buffer);
	       printf("Bytes read: %d\n", bytes_read);
	       for (int i = 0; i < bytes_read; i++) {
		    printf("%d ", (unsigned char)buffer[i]);
	       }
	       printf("\n");
	       char *body = parse_body(buffer);
	       char path[1024];
	       parse_path(buffer, path);
	       printf("path: %s\n", path);
	       if (strcmp(path, "/iflank") == 0) {
		    printf("remainder: %s\n", body);
		    printf("about to write\n");
		    write(to_iflank_pipe_rw[1], body,
			  buffer + bytes_read - body);
		    printf("just wrote: %s\n", body);

		    // flush if using FILE*, otherwise ensure child gets data
		    // fflush(iflank_stdin); // if you wrap pipe with fdopen

		    // read response from iflank
		    // int out_bytes;
		    while ((out_bytes =
			    read(from_iflank_pipe_rw[0], buffer,
				 BUF_SIZE)) > 0) {
			 buffer[out_bytes] = '\0';
			 printf("Output: %s\n", buffer);
			 char header[256];
			 int header_len;
			 header_len =
			     snprintf(header, sizeof(header),
				      "HTTP/1.1 200 OK\r\n"
				      "Content-Type: text/plain\r\n"
				      "Content-Length: %d\r\n" "\r\n",
				      out_bytes);
			 write(client_fd, header, header_len);	// forward to client
			 write(client_fd, buffer, out_bytes);	// forward to client
			 if (out_bytes < BUF_SIZE) {
			      break;	// stop if child has no more data
			 }
		    }
	       } else if (strcmp(path, "/") == 0) {
		    int fd = open("index.html", O_RDONLY);
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
