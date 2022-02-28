Question 1 : Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.
- $ ./mlfq.py -n 2 -j 2 -M 0 -c
+ Job 0 : Start Time : 0; Run Time : 84; I/O Frequency : 0. 
+ Job 1 : Start Time : 0; Run Time : 42; I/O Frequency : 0.
- Turnaround trung bình = (92 + 126)/2 = 109. 
- Response time trung bình = (0 + 10)/2 = 5.

Question 2 : How would you run the scheduler to reproduce each of the examples in the chapter?
//figure 8.2
> $ ./mlfq.py -n 3 -l 0,200,0 -q 10 -c

// Figure 8.3 Along Came An Interactive Job
> $ ./mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c

// Figure 8.4 A Mixed I/O-intensive and CPU-intensive Workload
> $ ./mlfq.py -n 3 -q 10 -l 0,175,0:50,25,1 -i 5 -S -c

// Figure 8.5 without priority boost
> $ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -c

// Figure 8.5 with priority boost
> $ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -B 50 -c

// Figure 8.6 without gaming tolerance
> $ ./mlfq.py -n 3 -q 10 -i 1 -S -l 0,200,0:80,100,9 -c

// Figure 8.6 with gaming tolerance
> $ ./mlfq.py -n 3 -q 10 -i 1 -l 0,200,0:80,100,9 -c

// Figure 8.7 Lower Priority, Longer Quanta
> $ ./mlfq.py -n 3 -a 2 -Q 10,20,40 -l 0,200,0:0,200,0 -c

