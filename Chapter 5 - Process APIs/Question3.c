#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
      int rc;
      rc = fork();
      if(rc < 0){
          printf("Fork failed\n");
      }
      else if(rc == 0){
          printf("Hello from child process!\n");
          exit(0);
      }
      else{
          sleep(2);
          printf("Goodbye from parent process!\n");
      }
      return 0;
}
