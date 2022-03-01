Question 1 : Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. 
Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address traces are hits or misses.
- Sau khi sử dụng -c đối với tổ hợp đầu tiên thì ta có các kết quả hit/miss như sau :
1. Đối với FIFO :
- Access 8 : cache sẽ là [] và sẽ có outcome là miss.
- Access 7 : cache sẽ là [8] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [8,7] và sẽ có outcome là miss.
- Access 2 : cache sẽ là [8,7,4] và sẽ có outcome là miss.
- Access 5 : cache sẽ là [7,4,2] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [4,2,5] và sẽ có outcome là hit.
- Access 7 : cache sẽ là [4,2,5] và sẽ có outcome là miss.
- Access 3 : cache sẽ là [2,5,7] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [5,7,3] và sẽ có outcome là miss.
- Access 5 : cache sẽ là [7,3,4] và sẽ có outcome là miss.

2. Đối với LRU :
- Access 8 : cache sẽ là [] và sẽ có outcome là miss.
- Access 7 : cache sẽ là [8] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [8,7] và sẽ có outcome là miss.
- Access 2 : cache sẽ là [8,7,4] và sẽ có outcome là miss.
- Access 5 : cache sẽ là [7,4,2] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [4,2,5] và sẽ có outcome là hit.
- Access 7 : cache sẽ là [4,2,5] và sẽ có outcome là miss.
- Access 3 : cache sẽ là [4,5,7] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [4,7,3] và sẽ có outcome là hit.
- Access 5 : cache sẽ là [4,7,3] và sẽ có outcome là miss.

3. Đối với OPT :
- Access 8 : cache sẽ là [] và sẽ có outcome là miss.
- Access 7 : cache sẽ là [8] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [8,7] và sẽ có outcome là miss.
- Access 2 : cache sẽ là [8,7,4] và sẽ có outcome là miss.
- Access 5 : cache sẽ là [7,4,2] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [7,4,5] và sẽ có outcome là hit.
- Access 7 : cache sẽ là [7,4,5] và sẽ có outcome là hit.
- Access 3 : cache sẽ là [7,4,5] và sẽ có outcome là miss.
- Access 4 : cache sẽ là [4,5,3] và sẽ có outcome là hit.
- Access 5 : cache sẽ là [4,7,3] và sẽ có outcome là hit.

Question 2 : For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU (worst-case reference streams cause the most misses possible). 
For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT?
- FIFO : ./paging-policy.py -s 0 --policy=FIFO -C 5 -a 0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5 -c
- LRU : ./paging-policy.py -s 0 --policy=LRU -C 5 -a 0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5 -c
- MRU : ./paging-policy.py -s 0 --policy=MRU -C 5 -a 0,1,2,3,4,5,4,5,4,5,4,5,4,5,4,5,4,5 -c
- Để đạt được OPT thì chúng ta cần tăng độ lớn của cache thêm 1 đơn vị. Tuy vậy đối với LRU thì dù có tăng hay không thì cũng không thay đổi. 

Question 3 : Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
- ./paging-policy.py -s 0 --policy=FIFO -C 4 -a 3,9,2,5,1,7,5,3,3,0,8,1,3,5,2,5,6,0,1,2,3,0,7,1,2,1,3,0,6,1,5,0 -c
- Đối với chuỗi ngẫu nhiên này thì sẽ dự đoán rằng FIFO sẽ thực hiện hiệu quả nhất, LRU có thể chỉ kém hơn 1 ít, còn MRU sẽ thực hiện kém hiệu quả nhất. 

Question 4 : Now generate a trace with some locality. How can you generate such a trace? 
How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with different numbers of clock bits?
- Để tạo ra một chuỗi có tính địa phương như vậy, chúng ta có thể viết một chương trình để tạo ra một chuỗi với phân phối chuẩn. 
- LRU sẽ chạy tốt trên chuỗi này, gần đạt được OPT.
- CLOCK sẽ chạy gần giống như RAND nhưng vẫn thấp hơn LRU
- CLOCK với nhiều clock bit hơn thì sẽ chạy tốt hơn cả LRU và RAND. 

Question 5 : Use a program like valgrind to instrument a real application and generate a virtual page reference stream. For example, running valgrind --tool=lackey --trace-mem=yes ls will output a nearly-complete reference trace of every instruction and data reference made by the program ls. To make this useful for the simulator above, you’ll have to first transform each virtual memory reference into a virtual page-number reference (done by masking off the offset and shifting the resulting bits downward). How big of a cache is needed for your application trace in order to satisfy a large fraction of requests? Plot a graph of its working set as the size of the cache increases.
- Chưa thực hiện được. 
