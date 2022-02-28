#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 1024

int main(){
    int rc, status, pid;
    int fd[2];
    char line[MAXLINE];
    rc = fork();

    if(pipe(fd) < 0){
        printf("Pipe failed\n");
    }
    if(rc < 0){
        printf("Fork failed\n");
    }
    else if(rc == 0){
        if(fork() == 0){
            close(fd[1]);
            printf("Receive message from the second child : %d\n", getpid());
            int n = read(fd[0], line, MAXLINE);
            write(STDOUT_FILENO, line, n);
            exit(0);
        }
        else{
            close(fd[0]);
            write(fd[1], "Hello from the first child.\n", 21);
            exit(0);
        }
    }
    return 0;
}
