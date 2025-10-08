#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE_SIZE 20
#define ST_FS 1
#define ST_CMD 2

int IN_TTY_MODE = 1;
char END_HTTP = '\0';

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
     // printf("changed to %s\n", path);
     return 0;
}

int ls(int state) {
     DIR *d = opendir(".");
     if (!d) {
	  perror("opendir");
	  return 1;
     }

     struct dirent *entry;
     while ((entry = readdir(d)) != NULL) {
          if(state == ST_FS){
               printf("<div>%s<a style='margin-left: 5px;' href='#' onclick='runCommand(\"cd %s\");'>click</a></div>", entry->d_name, entry->d_name);
          } else {

	  printf("%s\n", entry->d_name);
          }
     }
     closedir(d);
     return 0;
}

int in_cmd_dir(){
     DIR *d = opendir(".");
     if (!d) {
	  perror("opendir");
	  return 0;
     }

     struct dirent *entry;
     while ((entry = readdir(d)) != NULL) {
	  if(strcmp(entry->d_name, "blackbox.sh")){
            return 1;
       }
     }
     closedir(d);
     return 0;
}

void help(int state){
     if(state == ST_FS){
          printf("");
     } else if (state == ST_CMD){
          printf("<div>Actions: <a href='#' onclick='runCommand(\"r blackbox.sh\")'>Run</a></div>");
     }
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
	  // printf("Child exited with status %d\n", WEXITSTATUS(status));
     }

     return 0;
}

int main(int argc, char *argv[]) {
     char line[MAX_LINE_SIZE];
     char c;
     int state = ST_FS;
     for (int i = 1; i < argc; i++) {
	  if (strcmp(argv[i], "--http-mode") == 0) {
	       IN_TTY_MODE = 0;
	  }
     }
     if (IN_TTY_MODE == 1) {
	  printf("\nWelcome to iflank v0.1.5! Press Ctrl-D if you need to exit. FYI, iflank is a restricted shell without many of the features of a shell like bash.\n\n");
     } else {
	  // printf("Welcome to iflank v0.1.5!\n");
	  // fflush(stdout);
     }
     cd("/opt/homebrew/var/flank");
     pwd();
              printf("\n");
     ls(state);
     help(state);
     if(IN_TTY_MODE == 0){
          // printf("printftest");
	  fflush(stdout);
          char test[1];
          //test[0] = 'h';
          //test[1] = 'i';
          test[0] = '\0';
          write(STDOUT_FILENO, test, 1);
     }
     if (IN_TTY_MODE == 1) {
	  printf("iflank> ");
	  fflush(stdout);
     }
     int i = 0;
     while ((c = getchar()) != EOF) {
	  // printf("%d ", c);
	  // fflush(stdout);
       if(i == MAX_LINE_SIZE - 1){
            if(c != '\n'){
                 line[0] = '\0';	// reset it 
                 i = 0;
                 printf("line limit is %d characters! Input not accepted\n", MAX_LINE_SIZE - 1);
                 fflush(stdout);
                 continue;
            }
       }
	  if (c == '\n') {
	       if (line[i - 1] == '\r') {
		    line[i - 1] = '\0';
	       }
	       line[i] = '\0';
	       if (strcmp(line, "pwd") == 0) {
		    pwd();
	       } else if (strcmp(line, "help") == 0){
              help(state);
            }else if (strcmp(line, "ls") == 0) {
		    ls(state);
	       } else if (strncmp(line, "cd ", 3) == 0) {
		    char *dir = line + 3;
		    cd(dir);
              if(in_cmd_dir()){
                   state = ST_CMD;
                   pwd();
              printf("\n");
                   help(state);
              } else {
                   state = ST_FS;
                   pwd();
              printf("\n");
                   ls(state);
                   help(state);
              }
	       } else if (strncmp(line, "r ", 2) == 0) {
		    char *path = line + 2;
		    r(path);
              pwd();
              printf("\n");
              help(state);
	       } else {
		    printf("%s\n", line);
	       }
	       line[0] = '\0';	// reset it 
	       i = 0;
	       if (IN_TTY_MODE == 1) {
		    printf("iflank> ");
	       fflush(stdout);
	       } else {
	       fflush(stdout);
               write(STDOUT_FILENO, &END_HTTP, 1);
            }
	  } else {
	       line[i] = c;
	       i++;
	  }
     }
     printf("\n");
}
