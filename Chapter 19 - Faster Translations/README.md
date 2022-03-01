Question 1 : For timing, you’ll need to use a timer (e.g., gettimeofday()). How precise is such a timer? 
How long does an operation have to take in order for you to time it precisely? 
(this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully)
- gettimmeofday() là 1 lời gọi hệ thống nên sẽ bị sai lệch 1 vài mili(10^-3) giây. Do đó chúng ta cần phải lặp lại lời gọi này khoảng 1000 tới 2000 lần nữa và lấy trung bình của 
các lần gọi này để có thể đạt được kết quả với độ chính xác ở mức nano(10^-9) giây. 

Question 3 : Now write a script in your favorite scripting language (bash?) to run this program, 
while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. 
Run the script on different machines and gather some data. How many trials are needed to get reliable measurements?
- Có thể là ở khoảng 2^13 hoặc 2^14 trang thì kết quả đo sẽ hiệu quả. 

Question 5 : One thing to watch out for is compiler optimization. Compilers do all sorts of clever things, including removing loops which increment values that no other part of the program subsequently uses. How can you ensure the compiler does not remove the main loop above from your TLB size estimator?
- Compiler ở chương trình này không loại bỏ vòng lặp khỏi bộ dự tính độ lớn TLB của chúng ta nhưng để chắc chắn hơn thì ta có thể sử dụng 1 biến đếm và sau khi kết thúc thì ta sẽ in biến đếm đó ra. 

Question 7 : Another issue that might arise relates to initialization. If you don’t initialize the array a above before accessing it, the first time you access it will be very expensive, due to initial access costs such as demand zeroing. Will this affect your code and its timing? What can you do to counterbalance these potential costs?
- Điều này thường sẽ không ảnh hưởng tới code hiện thực và thời gian của nó. 
- Tuy vậy để giảm thiểu sự tốn kém thì ta nên thực hiện gọi hàm calloc() để khởi tạo mảng trước khi thực hiện đo thời gian.  

