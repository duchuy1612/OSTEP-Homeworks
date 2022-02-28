// Figure 8.2 Long-running Job Over Time
$ ./mlfq.py -n 3 -q 10 -l 0,200,0 -c

// Figure 8.3 Along Came An Interactive Job
$ ./mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c

// Figure 8.4 A Mixed I/O-intensive and CPU-intensive Workload
$ ./mlfq.py -n 3 -q 10 -l 0,175,0:50,25,1 -i 5 -S -c

// Figure 8.5 without priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -c

// Figure 8.5 with priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -B 50 -c

// Figure 8.6 without gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -S -l 0,200,0:80,100,9 -c

// Figure 8.6 with gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -l 0,200,0:80,100,9 -c

// Figure 8.7 Lower Priority, Longer Quanta
$ ./mlfq.py -n 3 -a 2 -Q 10,20,40 -l 0,200,0:0,200,0 -c
