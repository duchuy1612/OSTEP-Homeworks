Question 1 : Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). 
What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?
- Giá trị của biến trong child process chính là giá trị của biến đó.
- Khi cả parent process và child process đều thay đổi giá trị của x thì các biến cũng sẽ tự thay đổi ở bên trong các process đó.  

Question 2 : Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. 
Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
- Cả 2 process đều có thể truy cập tới file descriptor. 
- Khi ghi đè lên file một cách đồng thời thì kết quả thu được cuối cùng sẽ phụ thuộc vào scheduler của hệ thống. 

Question 3 : Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. 
You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?
- Chúng ta vẫn có thể hiện thực được điều này mà không sử dụng hàm wait() trong parent process, đó là sử dụng hàm kill() để gửi tín hiệu tiếp tục tới parent process hoặc đọc vào 
từ hàm pipe().

Question 4 : Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. 
See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe().
Why do you think there are so many variants of the same basic call?
- Lý do mà có nhiều biến thể của cùng một lời gọi đơn giản là để chúng ta có thể gọi hàm exec() theo nhiều cách khác nhau, nhằm phục vụ cho những chức năng khác nhau mà chúng ta
muốn thực thi. 

Question 5 : Now write a program that uses wait() to wait for the child process to finish in the parent. 
What does wait() return? What happens if you use wait() in the child?
- Nếu chạy thành công thì hàm wait() sẽ trả về process ID của child process đã kết thúc còn nếu gặp lỗi thì sẽ trả về -1.
- Nếu chúng ta sử dụng hàm wait() trong child process thì giá trị trả về sẽ là -1.

Question 6 : Write a slight modification of the previous program,this time using waitpid() instead of wait(). 
When would waitpid() be useful?
- Chúng ta nên dùng hàm waitpid() thay vì hàm wait() thông thường khi mà chúng ta có nhiều hơn 1 process nhưng chỉ thực sự quan tâm tới 1 process duy nhất nào đó. 

Question 7 : Write a program that creates a child process, and then in the child closes standard output (STDOUT_FILENO). 
What happens if the child calls printf() to print some output after closing the descriptor?
- Nếu child process gọi hàm printf() để in kết quả sau khi đã đóng descriptor thì kết quả của hàm printf() sẽ không được in ra màn hình. 

Question 8 : Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
