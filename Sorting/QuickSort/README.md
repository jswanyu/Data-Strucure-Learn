# 快速排序

## 一、概念及其介绍

快速排序使用分治法（Divide and conquer）策略来把一个串行（list）分为两个子串行（sub-lists）。

算法步骤：

1. 从数列中挑出一个元素，称为 "基准"（pivot）;
2. 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
3. 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序；



## 二、算法性能

|   算法   | 最好时间  | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :-------: | :------: | :------: | :------: | :----: |
| 快速排序 | O(nlogn） |  O(n^2)  | O(nlogn) | O(logn)  | 不稳定 |

快排的不稳定：

假设待排序数组: `a = [ 1, 2, 2, 3, 4, 5, 6 ];`

在快速排序的随机选择比较子(即pivot)阶段：

若选择a[2]（即数组中的第二个2）为比较子，而把大于等于比较子的数均放置在大数数组中，则a[1]（即数组中的第一个2）会到pivot的右边， 那么数组中的两个2非原序（这就是“不稳定”）。

若选择 a[1] （即数组中的第一个2）为比较子，而把小于等于比较子的数均放置在小数数组中，则数组中的两个 2 顺序也非原序 。

这就说明，quick sort是不稳定的。



## 三、过程图示

![快速排序示意图](https://github.com/wanyu416/Data-Strucure/blob/main/src/QuickSort.png)



## 四、实例代码

```c++
template<typename T>
void __QuickSort(T *arr, int l, int r) {
    if (l >= r)
        return;


    int p = __partition(arr, l, r);  //返回索引值
    __QuickSort(arr, l, p - 1);
    __QuickSort(arr, p + 1, r);
}

template<typename T>
void QuickSort(T *arr, int n) {
    __QuickSort(arr, 0, n - 1);
}
```



文件结构：

BubbleSort.h  冒泡排序算法

SelectionSort.h  选择排序算法

InsertionSort.h  插入排序算法

SortTestHelper.h  测试函数

main.cpp  主函数



## 五、改进

### 改进一：
