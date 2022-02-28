Question 1 : First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?
- Sẽ xảy ra lỗi segmentation fault (core dumped). 

Question 2 : Next, compile this program with symbol information included(with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. 
Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?
```bash
$ gcc -o -g null null.c
Program received signal SIGSEGV, Segmentation fault.
0x000055555555465e in main () at null.c:6
6		printf("%d\n", *ptr);
```

Question 3 : Finally, use the `valgrind` tool on this program. We’ll use the `memcheck` tool that is a part of `valgrind` to analyze what happens. 
Run this by typing in the following: `valgrind --leak-check=yes ./null` . What happens when you run this? Can you interpret the output from the tool?

Question 4 : Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? 
Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?
- Chương trình này sẽ chạy bình thường và không có lỗi gì. 
- Không dùng gdb được bởi vì gdb không thể phát hiện tràn bộ nhớ.
- Dùng `valgrind` có thể phát hiện được tràn bộ nhớ nhưng khi kết thúc process thì hệ điều hành sẽ lấy lại toàn bộ không gian bộ nhớ cho dù nó có tràn trong heap hay không. 

Question 5 : Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. 
What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
- Khi chạy thì chương trình sẽ chạy một cách bình thường. 
- Khi chạy mà sử dụng valgrind thì sẽ phát hiện ra `Invalid write of size 4`, xuất hiện dòng này là do chương trình đã lưu trữ dữ liệu int vào ô không thuộc stack và hàm malloc().
- Chương trình không hợp lý do size của int là 4 nên độ dài của array data phải là 25 chứ không phải 100. 

Question 6 : Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. 
Does the program run? What happens when you use valgrind on it?
- Chương trình vẫn chạy bình thường và in ra giá trị. 
- Khi sử dụng valgrind lên chương trình thì sẽ xảy ra lỗi đó là `Invalid write of size 4` như ở câu 5. 

Question 7 : Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
- Sẽ xảy ra runtime error. 
- Không cần sử dụng công cụ để phát hiện runtime error. 
