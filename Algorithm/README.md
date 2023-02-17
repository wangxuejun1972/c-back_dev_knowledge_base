#### 排序

| 排序算法 | 是否稳定 | 空间复杂度 | 最好时间复杂度 | 最坏时间复杂度 | 平均时间复杂度 |
| -------- | -------- | ---------- | -------------- | -------------- | -------------- |
| 冒泡排序 | √        | O(1)       | O(n)           | O(n^2)         | O(n^2)         |
| 选择排序 | ×        | O(1)       | O(n^2)         | O(n^2)         | O(n^2)         |
| 插入排序 | √        | O(1)       | O(n)           | O(n^2)         | O(n^2)         |
| 希尔排序 | ×        | O(1)       |                |                |                |
| 归并排序 | √        | O(n)       | nlogn          | nlogn          | nlogn          |
| 快速排序 | ×        | O(1)       | nlogn          | O(n^2)         | nlogn          |

#### 堆的应用

- 优先级队列

- Top K(剑指offer:40)

  **最大的K个数**,用小顶堆,维护一个大小为 K 的小顶堆，顺序遍历数组，从数组中取出数据与堆顶元素比较。如果比堆顶元素大，我们就把堆顶元素删除，并且将这个元素插入到堆中；如果比堆顶元素小，则不做处理，继续遍历数组。这样等数组中的数据都遍历完之后，堆中的数据就是前 K 大数据了。

  **最小的k个数**,用大顶堆

- 利用堆求中位数(剑指offer:41)

  维护两个堆，一个大顶堆，一个小顶堆。大顶堆中存储前半部分数据,小顶堆中存储后半部分数据，且小顶堆中的数据都大于大顶堆中的数据.

  为了实现平均分配,可以在数据的总数目是偶数时把新数据插入最小堆,否则插入最大堆.

  当数据总数是偶数时,如果新数据小于**最大堆**堆顶的元素,则先把这个新数据插入**最大堆**,接着把**最大堆**堆顶元素拿出来插入最小堆;	当数据总数是奇数时,如果新数据大于于**最小堆**堆顶的元素,则先把这个新数据插入**最小堆**,接着把**最小堆**堆顶元素拿出来插入最大堆; 