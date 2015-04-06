#常用数据结构c++实现

##Vector 向量
###概述
* **内部使用数组封装，支持随机访问**
* **空间复杂度**
 * 插入时，若容量不足会翻倍
 * 删除时，目前不会缩小占用内存


###构造函数和析构函数
1. **Vector(int c = DEFAULT_CAPACITY);**
 * 构造一个Vector，容量为c
* **Vector(Vector &s);**
 * 复制构造函数，包括_elem指向的内容也会拷贝
* **~Vector();**
 * 析构函数，会delete[] _elem

###整体属性
1. **int size();**
 * 返回Vector中元素个数

* **int capacity();**
 * 返回Vector的最大容量

* **bool empty();**
 * 判断是否为空。为空返回true

* **bool disordered();**
 * 是否非降序排列（true乱序 false有序）

###元素操作

1. **T& operator[](int r);**
 * 返回秩为r的元素的引用
 * 不检查数组越界

* **T get(int r);**
 * 返回秩为r的元素
 * 如果r超出范围，返回的是0

* **T last();**
 * 返回最后一个元素
 * 不检查数组越界

* **bool put(int r, T e);**
 * 将位置r处元素替换为e
 * 若r越界，返回false

* **bool insert(int r, T e);**
 * 在位置r处插入e 后面元素的后移
 * r的范围为0到size，越界返回false
 * 若容量不足，会按照2倍大小扩容

* **bool push_back(T e);**
 * 在最后面添加元素e
 * 若容量不足，会按照2倍大小扩容

* **T remove(int r);**
 * 删除秩为r的元素，并返回删除的元素
 * 如果r不符合范围，返回的是0

###排序查找

1. **void sort(enum sort_method method = QUICK);**
 * 按照非降排序
 * 需要使用<运算符进行比较
 * 参数指定排序方法 默认为快速排序
 * 可选方法：
  * 冒泡：BUBBLE
  * 快速排序（默认）：QUICK
  * 归并排序：MERGE

* **int find(T e);**
 * 查找e 返回下标
 * 若找不到 返回的是-1

* **int search(T e);**
 * 必须有序才能使用 返回不大于e的最大元素的位置
 * 返回值范围是-1到size-1

###遍历
1. **void travser(VST &visit);**
 * 遍历元素，对每个元素执行visit()操作


##List 列表

###概述
* **使用链表实现**
* **一个初始的List包含了哨兵头结点和尾结点**

###构造函数和析构函数

* **List()**
 * 大小初始化为0，头结点和尾结点互相指向
* **~List()**
 * 释放链表中所有结点的内存

###整体属性

* **int size();**
 * 返回元素个数

* **bool empty();**
 * 判断列表是否为空

* **bool disordered();**
 * 如果不是有序的，返回true

###元素操作
* **Posi(T) first();**
 * 返回第一个元素的位置
 * 若列表为空 返回的是尾结点的位置

* **Posi(T) last();**
 * 返回最后一个元素的位置
 * 若列表为空，返回的是头结点的位置

* **Posi(T) insertAsFirst(T e);**
 * 把e插入到列表的头部
 * 返回新插入结点的位置

* **Posi(T) insertAsLast(T e);**
 * 把e插入到列表的尾部
 * 返回新插入结点的位置

* **Posi(T) insertAfter(Posi(T) p, T e);**
 * 把e插入到p指向结点的后面
 * 不检查p是否有效

* **Posi(T) insertBefore(Posi(T) p, T e);**
 * 把e插入到p指向结点的前面
 * 不检查p是否有效

* **T remove(Posi(T) p);**
 * 删除p指向的结点
 * 不检查p是否有效

###排序查找

* **void sort();**
 * 按照非降顺序进行插入排序

* **Posi(T) find(T e);**
 * 查找元素e，返回第一个e的结点指针
 * 找不到时，返回NULL

* **Posi(T) search(T e);**
 * 有序列表查找，返回不大于e的最后一个元素结点位置

###遍历

* **template <typename VST> void travser(VST &visit);**
 * 遍历，对结点中每个元素执行visit()




#Stack 栈
###概述
* **从Vector派生而来**

###新增接口
* **void push(T const & e);**
 * 压栈
* **T pop();**
 * 出栈。返回出栈的元素
 * 栈为空时，返回的是0
* **T top();**
 * 返回栈顶元素
 * 栈空时，返回的是0


#Queue
###概述
* **从List派生而来**
* **目前没有检查有效性**
 * 队列为空时队首和队尾元素未知
 * 队列为空时出队操作会带来错误

###新增接口
* **void enqueue(T const & e);**
 * 入队
* **T rear();**
 * 返回队尾数据
* **T dequeue();**
 * 出队
* **T front();**
 * 返回队首数据


#Heap 堆
###概述
* **从Vector派生而来**

###新增接口
* **Heap(int c = DEFAULT_CAPACITY)**
 * 构造函数，大小指定为c
* **void heapify(int n);**
 * 对前n个元素批量建堆
* **void heapsort(int n);**
 * 对前n个元素进行堆排序


#BinTree 二叉树
###概述
* ****

#未完待续