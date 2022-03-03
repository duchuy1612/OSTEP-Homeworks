Question 1 : First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. 
Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. 
Does it point to the right lines of code? What other information does it give to you?

- Helgrind sẽ chỉ ra đúng đoạn code bị data race như đã dự đoán. 
- Ngoài ra nó cũng sẽ cho chúng ta biết địa chỉ nơi xảy ra sự đụng độ. 

Question 2 : What happens when you remove one of the offending lines of code? 
Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases?

- Khi loại bỏ 1 trong những đoạn code gây xâm phạm thì helgrind sẽ không phát hiện ra lỗi (No error).
- Đối với trường hợp chỉ thêm lock vào 1 trong những đoạn cập nhật giá trị của biến chung thì helgrind sẽ cảnh báo là có khả năng xảy ra data race (Possible data race).
- Đối với trường hợp thêm lock vào cả 2 đoạn cập nhật thì helgrind sẽ không phát hiện ra lỗi nào cả (No error).

Question 3 : Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). 
Can you see what problem it might have?

- Khi kiểm tra kỹ đoạn code này, ta có thể dễ dàng nhận ra thấy 2 thread đang tự lock lẫn nhau, đây chính là deadlock.

Question 4 : Now run helgrind on this code. What does helgrind report?

- Khi sử dụng helgrind để chạy đoạn code này thì helgrind sẽ báo cáo là đã vi phạm thứ tự của lock. 

Question 5 : Now run helgrind on main-deadlock-global.c. Examine the code; does it have the same problem that main-deadlock.c has? 
Should helgrind be reporting the same error? What does this tell you about tools like helgrind?

- Khi kiểm tra đoạn code này thì ta có thể thấy là nó cũng mắc lỗi tương tự đoạn code ở câu trước. 
- Đáng ra thì helgrind sẽ không báo cáo lỗi nào cả (do chúng ta đã giải quyết deadlock). 
- Điều này nhắc cho chúng ta một điều là không có công cụ nào là hoàn hảo cả, giống như việc không có thứ gọi là động cơ vĩnh cửu vậy.

Question 6 : Let’s next look at main-signal.c. This code uses a variable (done) to signal that the child is done and that the parent can now continue. 
Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?)

- Nếu thread child tốn nhiều thời gian để hoàn thành thì thread parent sẽ ở trong vòng lặp mà không làm gì cả. Do đó đoạn code này không hiệu quả. 

Question 7 : Now run helgrind on this program. What does it report? Is the code correct?

- Khi sử dụng helgrind trên chương trình này thì nó sẽ báo cáo có khả năng xảy ra data race tại các hàm done và printf(). 
- Đoạn code không thực sự chính xác do có khả năng xảy ra data race và có thể cho ra kết quả không chính xác.  

Question 8 : Now look at a slightly modified version of the code, which is found in main-signal-cv.c. 
This version uses a condition variable to do the signaling (and associated lock). 
Why is this code preferred to the previous version? Is it correctness, or performance, or both?

- Đoạn chương trình này đã được thêm biến điều kiện vào đi kèm với các lock. Việc sử dụng biến điều kiện sẽ đảm bảo cho độ chính xác cũng như thời gian chạy của chương trình. 
Do đó, chúng ta nên dùng chương trình này hơn là chương trình trước đó. 

Question 9 : Once again run helgrind on main-signal-cv. Does it report any errors?

- Khi sử dụng helgrind để chạy chương trình thì nó sẽ báo cáo là không có lỗi nào (No error). Lý do là chúng ta đã giải quyết data race của chương trình main-signal.c bằng 
việc sử dụng biến điều kiện trong chương trình main-signal-cv.  
