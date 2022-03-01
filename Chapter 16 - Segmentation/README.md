Question 1 : First let’s use a tiny address space to translate some addresses. Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?
```bash
segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
```
- Địa chỉ đầu tiên là 108 : ở dạng binary sẽ là 1101100(thuộc segment 1), bỏ đi bit đầu tiên ta sẽ được địa chỉ là 44 ở dạng thập phân. Segment 0 sẽ tăng theo chiều dương còn
segment 1 sẽ tăng theo chiều âm nên số đơn vị mà ta cần để đạt được 44 từ vị trí cuối sẽ là 44 - 64 = -20. Do |-20| = 20 <= 20 (giới hạn của segment 0 và segment 1 đều là 20) nên
địa chỉ này hợp lệ.
- Địa chỉ thứ 2 là 97 : ở dạng binary là 1100001(thuộc segment 1), bỏ đi bit đầu tiên ta sẽ được địa chỉ là 33 ở dạng thập phân. Tương tự như trên, số đơn vị mà ta cần để đạt được
33 từ vị trí cuối sẽ là 33 - 64 = -31. Do |-31| = 31 > 20 (giới hạn của segment 1) nên địa chỉ này sẽ không hợp lệ.
- Làm tương tự với các địa chỉ còn lại, ta thấy địa chỉ thứ 3 (53) hợp lệ, địa chỉ thứ 4 (33) không hợp lệ, địa chỉ thứ 5 (65) không hợp lệ. 

Question 2 : Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). 
What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? 
What are the lowest and highest illegal addresses in this entire address space? Finally, how would you run segmentation.py with the -A flag to test if you are right?
- Địa chỉ cho phép cao nhất trong segment 0 sẽ là 19 (chạy từ 0 - 19, do giới hạn là 20).
- Địa chỉ cho phép thấp nhất trong segment 1 sẽ là 128 - 20 = 108 (do giới hạn là 20, tăng theo chiều âm).
- Địa chỉ không cho phép thấp nhất sẽ là 20 còn địa chỉ không cho phép cao nhất sẽ là 107. 
- Để kiểm tra kết quả này, ta chạy chương trình bằng lệnh sau :
```bash
$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -A 19,108,20,107 -c
```

Question 3 : Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. 
What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters:
- Chúng ta sẽ set up base và các boundary như câu lệnh sau :
```bash
$ ./segmentation.py -a 16 -p 128 --b0 0 --l0 2 --b1 127 --l1 2 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 -c
```

Question 4 : Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). 
How should you configure the simulator to do so? Which parameters are important to getting this outcome?
- Chúng ta cần cấu hình simulator như sau để có thể có khoảng 90% địa chỉ ngẫu nhiên là hợp lệ :
```bash
./segmentation.py -a 100 -p 512 -n 1000 --b0 0 --l0 45 --b1 100 --l1 45 -c
```
- Các parameter quan trọng nhất để đạt được kết quả này là --l0, --l1 và --b1 vì chúng ta cần chúng để đưa cho segment 0 và segment 1 độ lớn bằng 90% không gian bộ nhớ tổng (--b1).

Question 5 : Can you run the simulator such that no virtual addresses are valid? How?
- Khi chúng ta cấu hình simulator với các thông số như sau thì chắc chắn sẽ không có địa chỉ nào hợp lệ : 
```bash
$ ./segmentation.py -a 16 -p 128 --b0 0 --l0 0 --b1 15 --l1 0 -s 1 -c
```
- Lý do là bởi --l0 và --l1 đều được đặt là 0 nên cả 2 segment sẽ không nhận được bất cứ % bộ nhớ nào cả. 
