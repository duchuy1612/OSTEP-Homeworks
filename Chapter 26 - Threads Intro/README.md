Question 1 : Let’s examine a simple program, “loop.s”. First, just read and understand it. 
Then, run it with these arguments(./x86.py -p loop.s -t 1 -i 100 -R dx) .
This specifies a single thread, an interrupt every 100 instructions, and tracing of register %dx. 
What will %dx be during the run? Use the -c flag to check your answers; 
the answers, on the left, show the value of the register (or memory value) after the instruction on the right has run.

- Giá trị ban đầu (giá trị khởi tạo) của %d sẽ là 0, còn trong lúc đang chạy sẽ có giá trị là -1.

Question 2 : Same code, different flags: (./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx).
This specifies two threads, and initializes each %dx to 3. 
What values will %dx see? Run with -c to check. Does the presence of multiple threads affect your calculations? Is there a race in this code?

- Giá trị khởi tạo của %dx là 3, trong lúc đang chạy sẽ giảm mỗi 1 đơn vị mỗi khi load adress là 1002 (rồi quay lại đầu queue là 1000), đến khi giảm còn -1 và load address là 1003
(halt), lúc này sẽ chuyển từ thread 0 sang thread 1 và giá trị của %dx cũng sẽ biến thiên tương tự như trên. 
- Việc sử dụng đa luồng không ảnh hưởng tới tính toán của chúng ta. 
- Không có race condition trong đoạn code này. 

Question 3 : Run this:./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx.
This makes the interrupt interval small/random; use different seeds (-s) to see different interleavings. Does the interrupt frequency change anything?

- Khi thêm interrupt vào thì ta có thể thấy thread 0 và thread 1 giảm giá trị %dx của riêng chúng, thay vì giảm trước trong thread 0, chuyển qua thread 1
rồi mới giảm trong thread 1 như trong câu 2. 

Question 4 : Now, a different program, looping-race-nolock.s, which accesses a shared variable located at address 2000; we’ll call this variable value. 
Run it with a single thread to confirm your understanding: ./x86.py -p looping-race-nolock.s -t 1 -M 2000.
What is value(i.e.,at memory address 2000) throughout the run? Use -c to check.

- Tại địa chỉ ô nhớ 2000, giá trị khởi tạo của %dx là 0, ở load address 1000 và 1001 (lệnh move và add) thì nó có giá trị là 0, sau đó tăng lên 1 và giữ nguyên cho tới khi load tới
đầu của queue và halt.

Question 5 : Run with multiple iterations/threads: ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000.
Why does each thread loop three times? What is final value of value?

- Lý do mỗi thread đều lặp 3 lần là vì chúng ta khởi tạo bx với giá trị là 3. 
- Giá trị của %dx tăng dần từ 0 lên 3 sau khi thread 0 lặp xong 3 lần và chuyển qua thread 1 cũng lặp 3 lần, %d tăng từ 3 lên 6. Do vậy giá trị cuối cùng của %dx là 6. 

Question 6 : Run with random interrupt intervals: ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 with different seeds (-s 1, -s 2, etc.).
Can you tell by looking at the thread interleaving what the final value of value will be? Does the timing of the interrupt matter? Where can it safely occur? Where not? 
In other words, where is the critical section exactly?

- Giá trị cuối cùng của %dx sẽ là 2 bởi vì tương tự như câu 3, khi thêm interrupt vào thì mỗi thread sẽ tăng giá trị %dx của riêng chúng. 
- Thời điểm interrupt sẽ ảnh hưởng tới %dx vì khi so sánh với không dùng interrupt thì %dx sẽ tăng ít hơn. 
- Sau khi thử nghiệm thì ta thấy nếu i nhỏ hơn 3 thì race condition sẽ diễn ra, như vậy thì i = 3 là giá trị an toàn nhất.

Question 7 : Now examine fixed interrupt intervals: ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1.
What will the final value of the shared variable value be? What about when you change -i 2, -i 3, etc.? 
For which interrupt intervals does the program give the “correct” answer?

- Giá trị cuối cùng của %dx sẽ là 1, khi i = 2 cũng sẽ là 1, còn với i = 3 thì giá trị này sẽ là 2. 
- Với khoảng thời gian là i >= 3 thì chương trình sẽ cho kết quả chính xác. 

Question 8 : Run the same for more loops (e.g., set -a bx=100). What interrupt intervals (-i) lead to a correct outcome? Which intervals are surprising?

- Khi chạy với 100 vòng lặp thì i phải >= 597 mới cho ra kết quả chính xác là 200. 
- Ngoài ra, ta cũng nhận ra một điều khá đặc biệt đó là khi chạy với các giá trị i là bội của 3 thì cũng cho kết quả chính xác. 

Question 9 : One last program: wait-for-me.s. Run: ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000.
This sets the %ax register to 1 for thread 0, and 0 for thread 1, and watches %ax and memory location 2000. 
How should the code behave? How is the value at location 2000 being used by the threads? What will its final value be?

- Đoạn code nên chạy 2 lệnh đầu (1000 và 1001) ở thread 0, sau đó chuyển sang chạy lệnh 1006 và halt. Còn những lệnh còn lại sẽ chạy ở thread 1 sau khi thread 0 kết thúc. 
- Thread 0 sẽ chuyển giá trị tại vị trí 2000 thành 1 rồi halt và chuyển sang thread 1, thread 1 sẽ sử dụng giá trị này như đánh dấu vòng lặp, tức là khi đạt giá trị 1 thì vòng
lặp sẽ kết thúc. 
- Giá trị cuối cùng sẽ là 1. 

Question 10 : Now switch the inputs: ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000.
How do the threads behave? What is thread 0 doing? How would changing the interrupt interval (e.g., -i 1000, or perhaps to use random intervals) change the trace outcome? 
Is the program efficiently using the CPU?

- Thread 0 sẽ chạy trong nhiều vòng lặp cho tới khi giá trị tại vị trí ô nhớ 2000 chuyển thành 1 thì mới chuyển sang thread 1, sau khi thread 1 halt và giá trị chuyển thành 0
thì chuyển sang lại thread 0. 
- Cho dù thay đổi i thành bất kỳ giá trị ngẫu nhiên nào thì cũng không làm thay đổi outcome. 
- Chương trình đang không dùng CPU một cách hiệu quả do thread 0 phải lặp lại khá nhiều và thread 1 phải đợi thread 0 khá lâu. 

