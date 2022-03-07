Question 1 : First let’s make sure you understand how the programs generally work, and some of the key options. Study the code in vector-deadlock.c, as well as 
in main-common.c and related files.
Now, run ./vector-deadlock -n 2 -l 1 -v, which instantiates two threads (-n 2), each of which does one vector add (-l 1), and does so in verbose mode (-v). 
Make sure you understand the output. How does the output change from run to run?

- Khi chạy ./vector-deadlock -n 2 -l 1 -v thì thứ tự của các thread sẽ có thể thay đổi trong các lần chạy khác nhau. 

Question 2 : Now add the -d flag, and change the number of loops(-l) from 1 to higher numbers. What happens? Does the code (always) deadlock?

- Khi thêm flag -d vào và cho chạy với số vòng lặp tăng dần từ 1 thì thứ tự của các thread sẽ bị thay đổi.
- Đoạn code không phải lúc nào cũng gặp deadlock. 

Question 3 : How does changing the number of threads (-n) change the outcome of the program? Are there any values of -n that ensure no deadlock occurs?

- Việc thay đổi giá trị của n sẽ ảnh hưởng tới sô thread có thể được chạy, do đó nó đóng phần quan trọng trong việc có xảy ra deadlock hoặc race condition hay không. 
- Với giá trị của n là 1 thì chắc chắn sẽ không xảy ra deadlock do chỉ có 1 thread chạy. 

Question 4 : Now examine the code in vector-global-order.c. First, make sure you understand what the code is trying to do; do you understand why the code avoids deadlock? 
Also, why is there a special case in this vector_add() routine when the source and destination vectors are the same?

- Đoạn code này có thể tránh deadlock là vì nó sắp xếp thứ tự của các lock theo địa chỉ của các lock đó. 
- Khi 2 vector hoàn toàn giống nhau cùng đợi chung 1 lock tận 2 lần thì sẽ gây ra deadlock. 

Question 5 : Now run the code with the following flags: -t -n 2 -l 100000 -d. How long does the code take to complete? 
How does the total time change when you increase the number of loops, or the number of threads?

- Đối với các flag đầu tiên thì thời gian chạy sẽ là 0.02 giây. 
- Khi tăng số vòng lặp lên thì thời gian sẽ tăng lên. (ở 1000000 là 0.19 giây còn ở 10000000 là 1.93 giây)
- Khi tăng số lượng thread thì thời gian cũng sẽ tăng lên. 

Question 6 : What happens if you turn on the parallelism flag (-p)? How much would you expect performance to change when each thread is working on adding different vectors (which is what -p enables) versus working on the same ones?

- Khi chúng ta thêm flag chạy song song -p thì các thread sẽ chạy song song mà không phải đợi lẫn nhau. 
- Thời gian sẽ giảm đi khi mỗi thread hiện thực những vector khác nhau. 

Question 7 : Now let’s study vector-try-wait.c. First make sure you understand the code. Is the first call to pthread_mutex_trylock() really needed? 
Now run the code. How fast does it run compared to the global order approach? How does the number of retries, as counted by the code, change as the number of threads increases?

- Chúng ta không thực sự cần lời gọi đầu của pthread_mutex_trylock() vì hàm này sẽ liên tục nhảy thay vì nghỉ ngơi trong lúc đợi như pthread_mutex_lock(). 
- Cách hiện thực này sẽ chạy với thời gian chậm hơn so với cách hiện thực ở câu 4. 
- Khi số thread tăng lên thì số retries sẽ tăng lên. 

Question 8 : Now let’s look at vector-avoid-hold-and-wait.c. 
What is the main problem with this approach? 
How does its performance compare to the other versions, when running both with -p and without it?

- Vấn đề chính với cách hiện thực này đó là việc chỉ có 1 thread được phép thực hiện tại 1 thời điểm. 
- Vấn đề sẽ thực sự xuất hiện khi chúng ta sử dụng flag -p và nó sẽ khiến cho thời gian hiện thực tăng lên cũng như việc sử dụng các thread sẽ không hiệu quả vì chúng sẽ cùng
phải đợi global lock. 

Question 9 : Finally, let’s look at vector-nolock.c. This version doesn’t use locks at all; does it provide the exact same semantics as the other versions? Why or why not?

Question 10 : Now compare its performance to the other versions, both when threads are working on the same two vectors (no -p) and when each thread is working on 
separate vectors (-p). How does this no-lock version perform?

- Phiên bản hiện thực không sử dụng lock này chạy với thời gian khá nhanh so với những phiên bản khác có sử dụng lock. 
