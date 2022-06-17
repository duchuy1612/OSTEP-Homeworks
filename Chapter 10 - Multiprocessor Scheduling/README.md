Question 1 : To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: ./multi.py -n 1 -L a:30:200. How long will it take to complete? Turn on the -c flag to see a final answer, and the -t flag to see a tick-by-tick trace of the job and how it is scheduled.
- Chương trình sẽ kết thúc trong 30ms do chỉ có 1 CPU và 1 công việc. 

Question 2 : Now increase the cache size so as to make the job’s working set (size=200) fit into the cache (which, by default, is size=100); for example, run ./multi.py -n 1 -L a:30:200 -M 300. Can you predict how fast the job will run once it fits in cache? (hint: remember the key parameter of the warm rate, which is set by the -r flag) Check your answer by running with the solve flag (-c) enabled.
- 10 chu kỳ đầu tiên sẽ chạy với thời gian như nhau.
- Nếu -r là 2 thì 20 chu kỳ tiếp theo sẽ chạy với thời gian là 10. 
- Do đó thời gian tổng sẽ là 10 + 20/2 = 20.

Question 3 : One cool thing about multi.py is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time with time left tracing enabled (-T). This flag shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick has run. What do you notice about how that second column decreases?
- Cột thứ 2 sẽ giảm đi nhanh hơn -r lần sau khi khởi động (10). 

Question 4 : Now add one more bit of tracing, to show the status of each CPU cache for each job, with the -C flag. For each job, each cache will either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example? What happens as you change the warmup time parameter (-w) to lower or higher values than the default?
- Tại time point 10 thì cache sẽ khởi động cho công việc 'a' trong ví dụ đơn giản trên. 
- Khi thay đổi thời gian khởi động thì vẫn sẽ chạy như bình thường cho tới time point thứ -w. 

Question 5 : At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? Oh yeah! So let’s start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50) Can you predict how long this will take, given a round-robin centralized scheduler? Use -c to see if you were right, and then dive down into details with -t to see a step-by-step and then -C to see whether caches got warmed effectively for these jobs. What do you notice?
- Các cache sẽ không thể giữ được cả 3 công việc cùng một lúc, do đó sẽ xảy ra hiện tượng 1 process liên tục xóa cache của các process khác. Chúng ta chỉ có thể sử dụng 2 core
để chạy các công việc 1 cách song song, do đó thời gian chạy sẽ là (100 + 100 + 100)/2 = 300/2 = 150.

Question 6 : Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the -A flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1; don’t forget to turn on various tracing options to see what is really happening! Can you predict how fast this version will run? Why does it do better? Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?
- Process 'a' chắc chắn sẽ hoàn thành công việc trước process 'b' và process 'c'. Do đó thời gian tổng cần để hoàn thành sẽ bằng thời gian warm-up của 2 process 'b' và 'c' + tổng thời gian còn lại của process B và C chia cho số core = 10 + 10 + (90 + 90)/2 = 110. 
- Như ở câu hỏi 5, bất cứ sự kết hợp nào của 'a', 'b','c' đều sẽ dẫn đến tăng thời gian cần để hoàn thành tất cả công việc do process 'a' sẽ liên tục xóa cache của process 'b'
và process 'c'. 

Question 7 : One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes you can speed up by more than a facor of N, a situation entitled super-linear speedup. To experiment with this, use the job description here (-L a:100:100,b:100:100,c:100:100) with a small cache (-M 50) to create three jobs. Run this on systems with 1, 2, and 3 CPUs (-n 1, -n 2, -n 3). Now, do the same, but with a larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use -c to confirm your guesses, and other tracing flags to dive even deeper.

```
$ ./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -T -C -M 50 -c     300
$ ./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -T -C -M 50 -c     150
$ ./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -T -C -M 50 -c     100

$ ./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -T -C -M 100 -c    300
//process a b c keeps evicting each other's cache content
$ ./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -T -C -M 100 -c    150
//process a b c has there individual cache content
$ ./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -T -C -M 100 -c    55
```
- Dự đoán đó là nếu chúng ta có thể chạy 1 công việc hoàn toàn trên process 'a' thì thời gian chạy sẽ nhanh hơn do lúc này các process sẽ sử dụng cache một cách hiệu quả hơn. 
