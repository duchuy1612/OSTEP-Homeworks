#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){
      int rc;
      rc = fork();
      char* args[] = {"ls", "-l", NULL};
      char* env[] = {NULL};
      if(rc < 0){
          printf("failed to fork\n");
      }
      else if(rc == 0){
          execvp("ls", args);
      }
      else{
          sleep(1);
          printf("Goodbye from parent\n");
      }
      return 0;
}
