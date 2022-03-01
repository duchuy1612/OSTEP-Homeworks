Question 1 : For timing, you’ll need to use a timer (e.g., gettimeofday()). How precise is such a timer? 
How long does an operation have to take in order for you to time it precisely? 
(this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully)
- gettimmeofday() là 1 lời gọi hệ thống nên sẽ bị sai lệch 1 vài mili(10^-3) giây. Do đó chúng ta cần phải lặp lại lời gọi này khoảng 1000 tới 2000 lần nữa và lấy trung bình của 
các lần gọi này để có thể đạt được kết quả với độ chính xác ở mức nano(10^-9) giây. 

Question 3 : Now write a script in your favorite scripting language (bash?) to run this program, 
while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. 
Run the script on different machines and gather some data. How many trials are needed to get reliable measurements?
- Có thể là khoảng 100000 vòng lặp thì kết quả đo sẽ hiệu quả. 

Question 5 : 

