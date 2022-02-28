#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h> 

int main(){
    int rc = fork();
    if (rc < 0){
      fprintf(stderr, "Fork failed\n");
      exit(EXIT_FAILURE);
    } 
    else if (rc == 0){
      pid_t wait_return = wait(NULL);
      printf("child wait return: %d\n", wait_return);
    } 
    else{
      pid_t wait_return = wait(NULL);
      printf("parent wait return: %d\n", wait_return);
    }
    return 0;
}
