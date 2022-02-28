Question 1 : Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
- Đối với SJF :
> $ ./scheduler.py -p SJF -l 200,200,200 -c
Cho kết quả là :
> response time: 0, 200, 400.
> turnaround time: 200, 400, 600.
- Đối với FIFO :
> $ ./scheduler.py -p FIFO -l 200,200,200 -c
>  Cho kết quả là :
response time: 0, 200, 400.
turnaround time: 200, 400, 600.

Question 2 : Now do the same but with jobs of different lengths: 100, 200, and 300.
- Đối với SJF :
> $ ./scheduler.py -p SJF -l 100,200,300 -c
- Cho kết quả là :
> response time: 0, 100, 300
> turnaround time: 100, 300, 600
- Đối với FIFO :
> $ ./scheduler.py -p FIFO -l 100,200,300 -c
- Cho kết quả là :
> response time: 0, 100, 300
> turnaround time: 100, 300, 600

Question 3 : Now do the same, but also with the RR scheduler and a time-slice of 1.
> $ ./scheduler.py -p RR -q 1 -l 100,200,300 -c
- Cho kết quả là : 
> response time: 0, 1, 2
> turnaround time: 298, 499, 600

Question 4 : For what types of work loads does SJF deliver the same turnaround times as FIFO?
- Khi mà các công việc được sắp xếp theo thứ tự độ dài thời gian từ thấp đến cao. 

Question 5 : For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
- Khi mà độ dài công việc là như nhau và quantum time cũng ngang bằng với độ dài công việc. 

Question 6 : What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?
- Thời gian phản hồi sẽ tăng nếu độ dài của các công việc tăng. 
- Simulator :
> $ ./scheduler.py -p SJF -l 200,200,200 -c
> $ ./scheduler.py -p SJF -l 300,300,300 -c
> $ ./scheduler.py -p SJF -l 400,400,400 -c

Question 7 : What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
- Khi độ dài của quantum time tăng thì thời gian phản hồi của Round Robin sẽ tăng theo. 
- Công thức sẽ là : T_worst = (i = 1)Sigma(n){min(job_i, T_quantum)}. 
