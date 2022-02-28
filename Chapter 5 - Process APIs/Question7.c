#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
      fprintf(stderr, "Fork failed\n");
      exit(EXIT_FAILURE);
    } 
    else if (pid == 0){
      close(STDOUT_FILENO);
      printf("Called from child.\n");
    } 
    else{
      wait(NULL);
      printf("Called from parent.\n");
    }
    return 0;
}
