## [编写一个类，实现简单的栈，栈中有以下操作：](stack.cc)

​	   > 元素入栈     void push(int);
​	   > 元素出栈     void pop();
​	   > 读出栈顶元素 int top();
​	   > 判断栈空     bool emty();
​	   > 判断栈满     bool full();
 如果栈溢出，程序终止。栈的数据成员由存放
 10个整型数据的数组构成。先后做如下操作：
​     > 创建栈
​     > 将10入栈
​     > 将12入栈
​     > 将14入栈
​     > 读出并输出栈顶元素
​     > 出栈
​     > 读出并输出栈顶元素

## 编写一个类，实现简单的队列。队列中有以下操作：

​    > 元素入队             void push(int);
​    > 元素出队             void pop();
​    > 读取队头元素         int front();
​    > 读取队尾元素         int back();
​    > 判断队列是否为空     bool emty();
​	   > 判断队列是否已满     bool full();

##### [链栈](listQueue.cc)

##### [数组实现栈](arrayQueue.cc)

## 在封装Linux下互斥锁和条件变量,并自行编写测试程序

[MutexCond](mutexcond/)