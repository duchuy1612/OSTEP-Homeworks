Question 1 : First, open two separate terminal connections to the same machine, so that you can easily run something in one window and the other.
Now,in one window, run vmstat 1, which shows statistics about machine usage every second. 
Read the man page, the associated README, and any other information you need so that you can understand its output. 
Leave this window running vmstat for the rest of the exercises below.
Now, we will run the program mem.c but with very little memory usage. This can be accomplished by typing ./mem 1 (which uses only 1 MB of memory). 
How do the CPU usage statistics change when running mem? Do the numbers in the user time column make sense? How does this change when running more than one instance of mem at once?

- User time sẽ tăng trong khi chương trình đang chạy còn thời gian rảnh sẽ giảm khi chương trình đang chạy. 
- Các con số trong cột user time khá hợp lý. 
- Khi chạy nhiều hơn 1 đơn vị bộ nhớ trong 1 lần thì user time sẽ tăng hệ số theo số đơn vị mà chúng ta muốn chạy. 

Question 2 : Let’s now start looking at some of the memory statistics while running mem. 
We’ll focus on two columns: swpd (the amount of virtual memory used) and free(the amount of idle memory). 
Run ./mem 1024 (which allocates 1024 MB) and watch how these values change. 
Then kill the running program (by typing control-c) and watch again how the values change. 
What do you notice about the values? In particular, how does the free column change when the program exits? 
Does the amount of free memory increase by the expected amount when mem exits?

- Các giá trị trong cột free sẽ không tăng một cách chính xác như dự đoán của chúng ta. 
- Cột free sẽ tăng khi chương trình bắt đầu chạy và sẽ giảm khi chương trình kết thúc. 
- Lượng bộ nhớ trống sẽ tăng như dự đoán khi mem tồn tại. 

Question 3 : We’ll next look at the swap columns(si and so), which indicate how much swapping is taking place to and from the disk. 
Of course, to activate these, you’ll need to run mem with large amounts of memory. 
First, examine how much free memory is on your Linux system (for example, by typing cat /proc/meminfo; 
type man proc for details on the /proc filesystem and the types of information you can find there). 
One of the first entries in /proc/meminfo is the total amount of memory in your system. Let’s assume it’s something like 8GB of memory; 
if so, start by running mem 4000(about 4 GB) and watching the swap in/out columns. Do they ever give non-zero values? 
Then, try with 5000, 6000, etc. What happens to these values as the program enters the second loop (and beyond), as compared to the first loop? 
How much data (total) are swapped in and out during the second, third, and subsequent loops? (do the numbers make sense?)
- Chưa trả lời được.

Question 4 : Do the same experiments as above, but now watch the other statistics(such as CPU utilization, and block I/O statistics). How do they change when mem is running?
- Khi mem đang chạy thì user time(us) sẽ tăng, cùng với đó số block I/O cũng sẽ tăng. 

Question 5 : Now let’s examine performance. Pick an input for mem that comfortably fits in memory (say 4000 if the amount of memory on the system is 8 GB). How long does loop 0 take (and subsequent loops 1, 2, etc.)? Now pick a size comfortably beyond the size of memory (say 12000 again assuming 8 GB of memory). How long do the loops take here? How do the bandwidth numbers compare? How different is performance when constantly swapping versus fitting everything comfortably in memory? Can you make a graph, with the size of memory used by mem on the x-axis, and the bandwidth of accessing said memory on the y-axis? Finally, how does the performance of the first loop compare to that of subsequent loops, for both the case where everything fits in memory and where it doesn’t?
- Chưa thực hiện được. 

Question 6 : Swap space isn’t infinite. You can use the tool swapon with the -s flag to see how much swap space is available. What happens if you try to run mem with increasingly large values, beyond what seems to be available in swap? At what point does the memory allocation fail?
- Khi chúng ta thử chạy mem với các giá trị với độ lớn tăng dần (lớn hơn nhiều so với những gì có trong swap) thì process sẽ bị kill ngay lập tức. 
- Khi đạt khoảng 90% bộ nhớ thì hoạt động cấp phát bộ nhớ sẽ thất bại. 

Question 7 : Finally, if you’re advanced, you can configure your system to use different swap devices using swapon and swapoff. Read the man pages for details. If you have access to different hardware, see how the performance of swapping changes when swapping to a classic hard drive, a flash-based SSD, and even a RAID array. How much can swapping performance be improved via newer devices? How close can you get to in-memory performance?
- Chưa trả lời được. 

