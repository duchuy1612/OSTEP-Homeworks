#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

long get_dt(long s1, long u1, long s2, long u2){
    return (s2-s1)*1e6 + (u2-u1);
}
int main(int argc, char **argv){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
  
    long PAGESIZE = sysconf(_SC_PAGESIZE);
    long jump = PAGESIZE / sizeof(int);
    int pages = atoi(argv[1]);
    int loops = atoi(argv[2]);
    struct timeval t;
    
    int *arr = malloc(sizeof(int)*pages*jump);
    for(int i = 0; i< pages*jump; i+=jump)
            arr[i] = 0;

    gettimeofday(&t, NULL);
    long tu = t.tv_usec;
    long ts = t.tv_sec;
    for(int k = 0; k < loops; k++)
        for(int i = 0; i< pages*jump; i+=jump)
            arr[i] += 1;
   
    gettimeofday(&t, NULL);
    printf("%lu\n", get_dt(ts, tu, t.tv_sec, t.tv_usec)/pages);
    return 0;
}
