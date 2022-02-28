#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    pid_t rc = fork();
    if (rc < 0){
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    } 
    else if (rc == 0){
      pid_t pid_return = waitpid(-1, NULL, WUNTRACED | WCONTINUED);
      printf("Child wait return: %d\n", pid_return);
    }
    else{
      pid_t pid_return = waitpid(rc, &status, WUNTRACED | WCONTINUED);
      printf("Parent wait return: %d\n", pid_return);
      printf("The child terminated normally: %s\n", WIFEXITED(status) ? "true" : "false");
    }
    return 0;
}
