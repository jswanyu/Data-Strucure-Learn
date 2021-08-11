# 冒泡排序

## 一、概念及其介绍

冒泡排序（Bubble Sort）也是一种简单直观的排序算法。它重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成。这个算法的名字由来是因为越小的元素会经由交换慢慢"浮"到数列的顶端。

比较相邻的元素。如果第一个比第二个大，就交换他们两个。对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。针对所有的元素重复以上的步骤，除了最后一个。持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。



## 二、算法性能

|   算法   | 最好时间 | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :------: | :------: | :------: | :------: | :----: |
| 冒泡排序 |  O(n）   |  O(n^2)  |  O(n^2)  |   O(1)   |  稳定  |

关于稳定性：因为在比较的过程中，当两个相同大小的元素相邻，只比较大或者小，所以相等的时候是不会交换位置的。而当两个相等元素离着比较远的时候，也只是会把他们交换到相邻的位置。他们的位置前后关系不会发生任何变化，所以算法是稳定的。



## 三、过程图示

![插入排序示意图](https://github.com/wanyu416/Data-Strucure/blob/main/src/bubbleSort.gif)



## 四、实例代码

```c++
template<typename T>
void BubbleSort(T *arr,int n)
{
	for (int i = 0; i < n - 1; i++) //对于n个数，每一轮比较冒出一个最大的数，最后一个数不用冒，所以要比较n-1轮
		for (int j = 0; j < n - 1 - i; j++) //n个数中，相邻的元素就有n-1组,第0轮要比较n-1次,第i轮要比较n-1-i次
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}
```



文件结构：

BubbleSort.h  冒泡排序算法

SelectionSort.h  选择排序算法

InsertionSort.h  插入排序算法

SortTestHelper.h  测试函数

main.cpp  主函数



## 五、改进

### 改进一：添加标志位，如果某次没有发生交换，则停止排序

```c++
template<typename T>
void BubbleSort(T *arr,int n)
{
    bool again = true;
	for (int i = 0; i < n - 1 && again; i++)                  //外层循环中只有标志位为真，才进行下一次排序
		for (int j = 0, again = false; j < n - 1 - i; j++)    //每次的内层循环将标志位设为假
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
    			again = true;                                 //发生交换就将标志位设为真
}
```

不过，这种改进并不很显著，因为在最坏情况下，改进过的冒泡排序过程跟未改进过的差不多。



### 改进二：暂时没看

来源：https://github.com/liuyubobobo/Play-with-Algorithms/blob/master/02-Sorting-Basic/Course%20Code%20(C%2B%2B)/Optional-02-Bubble-Sort/main.cpp

```c++
// 我们的第二版bubbleSort,使用newn进行优化
template<typename T>
void bubbleSort2( T arr[] , int n){

    int newn; // 使用newn进行优化

    do{
        newn = 0;
        for( int i = 1 ; i < n ; i ++ )
            if( arr[i-1] > arr[i] ){
                swap( arr[i-1] , arr[i] );

                // 记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
                newn = i;
            }
        n = newn;
    }while(newn > 0);
}
```

