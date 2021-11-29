# 选择排序

## 一、概念及其介绍

选择排序是一种简单直观的排序算法

首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。重复第二步，直到所有元素均排序完毕。



## 二、算法性能

|   算法   | 最好时间 | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :------: | :------: | :------: | :------: | :----: |
| 选择排序 | O(n^2）  |  O(n^2)  |  O(n^2)  |    1     | 不稳定 |

关于稳定性：选择排序是给每个位置选择当前元素最小的，比如给第一个位置选择最小的，在剩余元素里面给第二个元素选择第二小的，依次类推，直到第n - 1个元素，第n个元素不用选择了，因为只剩下它一个最大的元素了。那么，在一趟选择，如果当前元素比一个元素小，而该小的元素又出现在一个和当前元素相等 的元素后面，那么交换后稳定性就被破坏了。

比较拗口，举个例子，序列5 8 5 2 9，我们知道第一遍选择第1个元素5会和2交换，那么原序列中2个5的相对前后顺序就被破坏了，所以选择排序不是一个稳定的排序算法。



## 三、过程图示

[![5TL4C4.gif](https://z3.ax1x.com/2021/10/27/5TL4C4.gif)](https://imgtu.com/i/5TL4C4)



## 四、实例代码

```java
public class SelectionSort {
    public static <E extends Comparable<E>> void sort(E[] arr){
        for (int i = 0; i < arr.length; i++) {
            //寻找[i,n)区间里的最小值
            int minIndex = i;    //最小值的索引为i
            for (int j = i+1; j < arr.length; j++)   //从i的下一个数开始
                //如果找到一个比第i个数小的数，就把他所在的索引记为当前轮次的最小值
                if (arr[j].compareTo(arr[minIndex])<0) 
                    minIndex = j;
            swap(arr,i,minIndex);  //将最小值交换到第i个数处
        }
    }

    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```







## 五、改进

### 改进一：减少不必要的交换次数

这里有一个问题就最后一步交换过程总会发生，如果元素的位置本身就是合理的，其实没必要交换，会带来3次冗余移动，可以加一个条件语句，再判定是否要交换

```java
public class SelectionSort {
    public static <E extends Comparable<E>> void sort(E[] arr){
        for (int i = 0; i < arr.length; i++) {
            int minIndex = i;   
            for (int j = i+1; j < arr.length; j++)   
                if (arr[j].compareTo(arr[minIndex])<0) 
                    minIndex = j;
            if(i != minIndex)//比较索引即可，无需比较具体数据
            	swap(arr,i,minIndex);  
        }
    }

    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```

上述改进将在程序中引入新的条件以增加n-1次比较，这样的改善是否有必要呢?这取决于排序元素的类型，如果元素是**数字或字符**，那么引入新的条件来避免冗余交换，其实效率并没有提高多少；如果data中的元素是大的**复合实体，如数组或结构**，那么一次交换(需要3次赋值)可能需要花费相当于100次索引比较的时间，因此建议使用有条件的swap操作。



### 改进二：双指针法--每一轮中可以同时找到当前未处理元素的最大值和最小值

来源：https://github.com/liuyubobobo/Play-with-Algorithms/blob/master/02-Sorting-Basic/Course%20Code%20(Java)/Optional-01-Optimized-Selection-Sort/src/bobo/algo/SelectionSort2.java

```c++
// 在每一轮中, 可以同时找到当前未处理元素的最大值和最小值
public class SelectionSort2 {
    private SelectionSort2(){}

    public static void sort(Comparable[] arr){
        //左右指针
        int left = 0, right = arr.length - 1;
        while(left < right){
            int minIndex = left;
            int maxIndex = right;

            // 在每一轮查找时, 要保证arr[minIndex] <= arr[maxIndex]
            if(arr[minIndex].compareTo(arr[maxIndex]) > 0)
                swap(arr, minIndex, maxIndex);

            for(int i = left + 1 ; i < right; i ++)
                if(arr[i].compareTo(arr[minIndex]) < 0)
                    minIndex = i;
                else if(arr[i].compareTo(arr[maxIndex]) > 0)
                    maxIndex = i;

            swap(arr, left, minIndex);
            swap(arr, right, maxIndex);

            left ++;
            right --;
        }
    }

    private static void swap(Object[] arr, int i, int j) {
        Object t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```

