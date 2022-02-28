#define _GUN_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sched.h>
#include<sys/time.h>
#include<fcntl.h>

int main(){
    //system call
    struct timeval time_before, time_after;
    suseconds_t time_sum;
    int fd, loops = 10000;
    fd = open("./data.input", O_RDONLY);
    
    gettimeofday(&time_before, NULL);
    for(int i = 0; i < loops; i++){
        read(fd, NULL, 0);
    }
    gettimeofday(&time_after, NULL);
    printf("The average time of system call is : %f microseconds\n", (1000000 * time_after.tv_sec + time_after.tv_usec - 1000000 * time_before.tv_sec - time_before.tv_usec) / (float)loops);

    //context switch
    int first_pipe[2];
    int second_pipe[2];
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0, &cpu_set);
    if(pipe(first_pipe) < 0){
        printf("pipe error\n");
        exit(1);
    }
    if(pipe(second_pipe) < 0){
        printf("pipe error\n");
        exit(1);
    }
    int rc;
    rc = fork();
    if(rc < 0){
        printf("Fork failed\n");
    }
    else if(rc == 0){
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);
        for(int i = 0; i < loops; i++){
            write(first_pipe[0], NULL, 0);
            read(second_pipe[1], NULL, 0);
        }
    }
    else{
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);
        gettimeofday(&time_before, NULL);
        for(int i = 0; i < loops; i++){
            write(second_pipe[0], NULL, 0);
            read(first_pipe[1], NULL, 0);
        }
        gettimeofday(&time_after, NULL);
        printf("The average time of context switch is : %f microseconds\n", (1000000 * time_after.tv_sec + time_after.tv_usec - 1000000 * time_before.tv_sec - time_before.tv_usec) / (float)loops);
    }
    return 0;
}
