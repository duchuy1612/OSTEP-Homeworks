Question 1 : Run process-run.py with the following flags: -l 5:100,5:100. 
What should the CPU utilization be (e.g., the percent of time the CPU is in use?). Why do you know this? Use the -c and -p flags tosee if you were right.
- CPU sử dụng trong quá trình (% thời gian CPU được sử dụng) là 100%. Lý do là vì không có quá trình Input/Output nào cả. 

Question 2 : Now run with these flags: ./process-run.py -l 4:100,1:0.
These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done.
How long does it take to complete both processes? Use -c and -p to find out if you were right.
- Cần phải tốn 11ms để hoàn thành cả 2 quá trình, trong đó tốn 5ms cho process 0 (sử dụng CPU), 6ms cho process 1 (sử dụng I/O). 

Question 3 : Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)
- Khi này thì điều sẽ xảy ra là process 1 sẽ chạy khi process 0 đang đợi cho I/O hoàn thành. 
- Việc thay đổi thứ tự sẽ dẫn đến thay đổi về thời gian cần để hoàn thành cả 2 quá trình. Process 0 khi ở trong trạng thái đợi thì process 1 sẽ chạy, nhờ vào đó mà thời gian sẽ
giảm xuống còn 7ms. 

Question 4 : We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. 
With the flag set to SWITCH_ON_END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. 
What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH_ON_END), one doing I/O and the other doing CPU work?
- Khi chạy 2 process trong đó 1 process thực hiện I/O và process còn lại thực hiện công việc của CPU thì process 1 sẽ không chạy khi process 0 đang đợi I/O. 

Question 5 : Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH_ON_IO). 
What happens now? Use -c and -p to confirm that you are right.
- Khi sử dụng SWITCH_ON_IO thì khi process 0 đang trong trạng thái đợi I/O thì sẽ chuyển sang process 1 và khi process 1 thực hiện xong thì process 0 mới tiếp tục để hoàn thành I/O.

Question 6 : One other important behavior is what to do when an I/O completes. 
With -I IO_RUN_LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. 
What happens when you run this combination of processes? 
(Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p) Are system resources being effectively utilized?
- Process 0 sẽ chạy I/O đầu tiên và rồi đợi các process khác thực hiện xong mới chạy các I/O còn lại.
- Nếu thực hiện chạy các process theo kiểu này thì tài nguyên của hệ thống sẽ không được sử dụng một cách hiệu quả. 

Question 7 : Now run the same processes, but with -I IO_RUN_IMMEDIATE set, which immediately runs the process that issued the I/O. 
How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?
- Lúc này thì các process khác có thể chạy trong khi process 0 đang trong trạng thái đợi I/O.
- Lý do việc chạy lại 1 process mới hoàn thành I/O là một ý tưởng tốt đó là khi chạy như này thì các process sẽ chạy công bằng với nhau hơn và nhờ đó giảm thiểu được thời gian phản hồi. 

Question 8 : Now run with some randomly generated processes: -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,3:50. 
See if you can predict how the trace will turn out. 
What happens when you use the flag -I IO_RUN_IMMEDIATE vs. -I IO_RUN_LATER? What happens when you use -S SWITCH_ON_IO vs. -S SWITCH_ON_END?
- Khi chạy process đầu tiên thì đầu tiên process sẽ chạy CPU, sau đó bắt đầu chạy I/O và vào trạng thái đợi I/O, lúc này process 1 sẽ bắt đầu chạy CPU, sau khi process 1 thực hiện xong
thì process 0 vẫn nằm trong trạng thái đợi trong 2ms nữa rồi mới kết thúc I/O đầu tiên và tiếp tục thực hiện I/O thứ hai. Tổng thời gian sẽ là 15ms. Khi thêm flag IO_RUN_IMMEDIATE thì
và IO_RUN_LATER thì vẫn chạy tương tự như ban đầu. Khi sử dụng -S SWITCH_ON_IO thì vẫn chạy tương tự như ban đầu còn -S SWITCH_ON_END thì process 0 phải đợi 2 lần I/O xong thì 
process 1 mới chạy CPU và do đó thời gian sẽ tăng lên thành 18ms.
