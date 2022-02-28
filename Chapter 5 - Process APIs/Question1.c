#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int x = 100;
    int rc = fork();
    if (rc < 0){
      fprintf(stderr, "Fork failed\n");
      exit(EXIT_FAILURE);
    } 
    else if (rc == 0){
      x = 101;
      printf("x is in child process: %d\n", x);
    } 
    else{
      x = 102;
      printf("x is in parent process: %d\n", x);
      wait(NULL);
    }
  return 0;
}
