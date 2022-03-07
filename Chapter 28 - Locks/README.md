Question 2 : When you run with the defaults, does flag.s work? Use the -M and -R flags to trace variables and registers (and turn on -c to see their values). 
Can you predict what value will end up in flag?

- Giá trị cuối cùng của flag sẽ là 0. 

Question 3 : Change the value of the register %bx with the -a flag(e.g., -a bx=2,bx=2 if you are running just two threads). 
What does the code do? How does it change your answer for the question above?

- Giá trị của %bx chính là số vòng lặp mà các thread sẽ chạy. Do đó nếu chúng ta chạy 2 thread thì mỗi thread đó sẽ lặp lại 2 lần. Trong khi đó giá trị của flag vẫn sẽ là 0. 

Question 4 : Set bx to a high value for each thread, and then use the -i flag to generate different interrupt frequencies; what values lead to a bad outcomes? 
Which lead to good outcomes?

- Sau khi tăng bx lên và sử dụng flag -i để thử các giá trị từ 1 tới 16 thì ta nhận thấy chỉ có các giá trị 11,15,16 là sẽ cho kết quả tốt, còn các giá trị còn lại sẽ cho kết quả xấu. 

Question 5 : Now let’s look at the program test-and-set.s. First, try to understand the code, which uses the xchg instruction to build a simple locking primitive. 
How is the lock acquire written? How about lock release?

- Sau khi đọc xong đoạn code và các hướng dẫn, để kích hoạt một lock, khi chạy ta sẽ sử dụng dòng lệnh : xchg %ax, mutex. 
- Còn để mở khóa lock đó ra ta có dòng lệnh : mov $0, mutex.

Question 6 : Now run the code, changing the value of the interrupt interval (-i) again, and making sure to loop for a number of times. Does the code always work as expected? Does it sometimes lead to an inefficient use of the CPU? How could you quantify that?

- Đoạn code sẽ không phải lúc nào cũng chạy như dự đoán. Trong nhiều lần chạy sẽ bị sai. 
- Thỉnh thoảng đoạn code sẽ có dẫn tới việc dùng CPU một cách không hiệu quả lắm do mutex là 0. 

Question 7 : Use the -P flag to generate specific tests of the locking code. For example, run a schedule that grabs the lock in the first thread, but then tries to acquire it in the second. Does the right thing happen? What else should you test?
