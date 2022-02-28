Question 1 : Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.
> $ ./mlfq.py -n 2 -j 2 -M 0 -c
+ Job 0 : Start Time : 0; Run Time : 84; I/O Frequency : 0. 
+ Job 1 : Start Time : 0; Run Time : 42; I/O Frequency : 0.
- Turnaround trung bình = (92 + 126)/2 = 109. 
- Response time trung bình = (0 + 10)/2 = 5.

Question 2 : How would you run the scheduler to reproduce each of the examples in the chapter?
// Figure 8.2
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

Question 3 : How would you configure the scheduler parameters to behave just like a round-robin scheduler? 
- Để cấu hình cho các thông số của scheduler biểu hiện như 1 scheduler sử dụng Round-Robin thì ta cần đặt timeslice <= (độ dài của công việc ngắn nhất) / (số lượng công việc).

Question 4 : Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.
> $ ./mlfq.py -n 3 -l 0,200,0:50,99,9 -i 1 -S -c

Question 5 : Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?
- Thời gian giữa các lần boost các công việc lên hàng đợi ưu tiên có level cao nhất = quantum time / 5% = 200 ms. 

Question 6 : One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.
- Khi không sử dụng -I thì công việc mà vừa thực hiện xong I/O sẽ được thêm vào cuối của hàng đợi và sẽ dẫn tới tăng thời gian phản hồi, không thực sự hiệu quả.  
