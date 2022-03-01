Question 1 : With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. 
How many registers do you need to locate a two-level page table? A three-level table?
- Đối với bảng có 2 tầng thì chúng ta nên cần 2 registers, còn bảng 3 tầng thì nên cần 3 registers.
- Tuy vậy vẫn có thể chỉ dùng 1 register vì chỉ có địa chỉ của bảng trang đầu tiên cần được lưu trong register.

Question 2 : Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. 
How many memory references are needed to perform each lookup?
- Đối với địa chỉ ảo đầu tiên : 0x611c (0b 11000 01000 11100), bỏ đi 5 bit cuối ta tách ra được thành 11000(24)(0x18) và 01000(8)(0x8). Nhìn lại dòng chứa trang thứ 108 (directory
được lưu trữ trong trang này), ở vị trí thứ 24 là a1, 0xa1 -> 0b 1 0100001 -> 33. Nhìn lại dòng chứa trang thứ 33, ở vị trí thứ 8 là b5, 0xb5 -> 0b1 0110101 -> 53. Từ đây suy ra 
được vị trí cần tìm là page[33][53] -> 0x6bc -> Value : 08.

Question 3 : Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? 
Will they lead to lots of cache hits (and thus fast accesses?) 
Or lots of misses (and thus slow accesses)?
- Theo như cách hiểu của mình về cách hoạt động của cache thì các directory của trang sẽ được lưu bên ngoài không gian bộ nhớ khi chương trình đang chạy trong hệ thống. Do đó thì
mỗi TLB miss sẽ dẫn tới 2 hoặc nhiều hơn TLB miss khác, do đó sẽ làm tăng số lượng miss và làm chậm các tiến trình. 

