Question 1 : First run with the flags -n 10 -H 0 -p BEST -s 0 to generate a few random allocations and frees. 
Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?
- free() sẽ luôn return 0 còn alloc() sẽ return ra giá trị = địa chỉ của list + size. 
- Free list sẽ tăng size lên dần tới 4. 
- Bộ nhớ vật lý sẽ bị chia thành các khối nhỏ, do đó dần dần theo thời gian thì size của vùng không gian trống sẽ chỉ còn lại 1. 

Question 2 : How are the results different when using a WORST fit policy to search the freelist(-p WORST)? What changes?
- Lúc này thì bộ nhớ sẽ bị chia thành nhiều khối nhỏ hơn nữa và dẫn tới việc phải tìm kiếm nhiều phần tử hơn. 

Question 3 : What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?
- Lúc này thì số lượng phần tử phải tìm kiếm sẽ giảm hơn nhiều so với WORST fit hay BEST fit do không cần phải tìm những phần tử để fit điều kiện WORST hay BEST. Nhờ đó mà
việc cấp phát sẽ diễn ra nhanh hơn. 

Question 4 : For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies.
Use the different free list orderings(-l ADDRSORT,-l SIZESORT+,-l SIZESORT-) to see how the policies and the list orderings interact.
- FIRST fit sẽ không bị ảnh hưởng cho dù sắp xếp theo kiểu nào vì nó chỉ cần tìm phần tử đầu tiên phù hợp.
- BEST fit và WORST fit sẽ được hưởng lợi từ SIZESORT+/SIZESORT- do khi đó các phần tử lớn nhất và nhỏ nhất sẽ được tìm một cách dễ dàng vì chúng nằm ở đầu của list. 

Question 5 : Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). 
What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). 
What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?
- Các yêu cầu cấp phát bộ nhớ lớn theo thời gian đều sẽ trả về NULL. 
- Khi sử dụng coalesing thì việc sắp xếp bằng địa chỉ(ADDRSORT) sẽ diễn ra một cách dễ dàng và hiệu quả hơn lúc không có coalesing. Đối với 2 kiểu sắp xếp còn lại thì WORST fit sẽ
hoạt động không hiệu quả còn BEST fit sẽ hoạt động như cũ, điều tương tự cũng xảy ra với FIRST fit. 

Question 6 : What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?
- Nếu -P có giá trị lớn hơn 50 thì hệ thống sẽ dần trở nên đầy (khi đạt 100) và sẽ không còn bộ nhớ dư để cấp phát. 
- Khi % tăng thì tỷ lệ đạt được các lần cấp phát thành công sẽ giảm do càng tiến về 100 thì sẽ càng ít bộ nhớ để cấp phát. 
- Khi % tiến về 0 thì các con trỏ sẽ được giải phóng khỏi bộ nhớ. 

Question 7 : What kind of specific requests can you make to generate a highly-fragmented free space? 
Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.
- Không thể có một list như vậy nếu chúng ta sort by address hay bật coalesing lên. 
