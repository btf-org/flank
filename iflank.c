#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE_SIZE 20

int TTY_MODE = 1;

void pwd() {
     char buf[1024];
     if (getcwd(buf, sizeof(buf)) != NULL) {
	  printf("%s\n", buf);
     } else {
	  perror("getcwd");
     }
}

int cd(const char *path) {
     if (chdir(path) != 0) {
	  perror("chdir");
	  return 1;
     }
     printf("changed to %s\n", path);
     return 0;
}

int ls() {
     DIR *d = opendir(".");
     if (!d) {
	  perror("opendir");
	  return 1;
     }

     struct dirent *entry;
     while ((entry = readdir(d)) != NULL) {
	  printf("%s\n", entry->d_name);
     }
     closedir(d);
     return 0;
}

int r(const char *path) {
     pid_t pid = fork();

     if (pid < 0) {
	  perror("fork failed");
	  return 1;
     }

     if (pid == 0) {
	  // Child: replace process image with the script
	  char *argv[] = { "/bin/bash", (char *)path, NULL };
	  execv("/bin/bash", argv);
	  perror("execv failed");	// only runs if exec fails
	  _exit(1);
     } else {
	  // Parent: wait for child to finish
	  int status;
	  waitpid(pid, &status, 0);
	  printf("Child exited with status %d\n", WEXITSTATUS(status));
     }

     return 0;
}

int main(int argc, char *argv[]) {
     cd("/opt/homebrew/var/flank");
     char line[MAX_LINE_SIZE];
     char c;
     int i = 0;
     for (int i = 1; i < argc; i++) {
	  if (strcmp(argv[i], "--http-mode") == 0) {
	       TTY_MODE == 0;
	  }
     }
     if (TTY_MODE == 1) {
	  printf("\nWelcome to iflank! Some notes:\n");
	  printf("  - Press Ctrl-D if you need to exit\n");
	  printf
	      ("  - iflank is a restricted shell without many of the features of a shell like bash\n");
	  printf("\n");
     }
     if (TTY_MODE == 1) {
	  printf("iflank> ");
	  fflush(stdout);
     }
     while ((c = getchar()) != EOF) {
	  // printf("%d ", c);
	  // fflush(stdout);
	  if (c == '\n') {
	       if (line[i - 1] == '\r') {
		    line[i - 1] = '\0';
	       }
	       line[i] = '\0';
	       if (strcmp(line, "pwd") == 0) {
		    pwd();
	       } else if (strcmp(line, "ls") == 0) {
		    ls();
	       } else if (strncmp(line, "cd ", 3) == 0) {
		    char *dir = line + 3;
		    cd(dir);
	       } else if (strncmp(line, "r ", 2) == 0) {
		    char *path = line + 2;
		    r(path);
	       } else {
		    printf("%s\n", line);
	       }
	       line[0] = '\0';	// reset it 
	       i = 0;
	       if (TTY_MODE == 1) {
		    printf("iflank> ");
	       }
	       fflush(stdout);
	  } else {
	       line[i] = c;
	       i++;
	  }
     }
     printf("\n");
}
