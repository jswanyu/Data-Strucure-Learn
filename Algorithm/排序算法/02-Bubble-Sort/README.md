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

![bubbleSort](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/bubbleSort%E7%A4%BA%E6%84%8F%E5%9B%BE.gif)



## 四、实例代码

```java
public class BubbleSort {
    
    public static <E extends Comparable<E>> void sort(E[] arr){
        //对于n个数，要进行n-1轮循环，每一轮将最大的数冒到最后面去
        for (int i = 0; i < arr.length-1; i++) {
            //n个数中，相邻的元素就有n-1组，第0轮要比较n-1次，第i轮要比较n-1-i
            for (int j = 0; j < arr.length-1-i; j++) {
                if (arr[j].compareTo(arr[j+1])>0)
                    swap(arr,j,j+1);
            }
        }
    }
}
```





## 五、改进

### 改进一：添加标志位，如果某次没有发生交换，则停止排序

适合本身就有序的序列，比如 2  3   5   7   8，扫描一次剩下的元素发现没有元素需要交换，说明此时数组已经有序了，程序提前终止

对于完全有序的数组，它就成了O(n)复杂度（如果是原始的写法对于完全有序的数组还是O(n^2)）

对于完全随机的这种改进并不很显著，因为在较坏情况下，改进过的冒泡排序过程跟未改进过的差不多。

```c++
public class BubbleSort {
    
    public static <E extends Comparable<E>> void sort(E[] arr){
        //设置一个标志，如果这一趟发生了交换，则为true，否则为false。如果有一趟没有发生交换，说明排序已经完成
        boolean sorted = true;  //第一次判断时标志位为true
        //外层循环需要flag为true
        for (int i = 0; i < arr.length-1 && sorted; i++) {
            //每次的内层循环将标志位设为假，否则没意义
            sorted = false;
            //内层循环会执行到底
            for (int j = 0; j < arr.length-1-i; j++) {
                if (arr[j].compareTo(arr[j+1])>0){
                    swap(arr,j,j+1);
                    sorted = true;
                }
            }
        }
    }
}
```



### 改进二：减少内层循环比较的元素

对于每次循环已经冒出去的值，可以不用去考虑它，在内层循环中记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑。比如  3  7  1  2  8  9，第一轮的冒泡会变为  3  1   2   7   8   9 ，最后一次交换位置就是在交换完7之后，那么此后的元素均不用考虑了，都已经放到了合适的位置

```java
public class BubbleSort {
    
	public static void sort(Comparable[] arr){
    for (int i = 0; i + 1 < arr.length; ) {
        int lastSwappedIndex = 0;
        for (int j = 0; j < arr.length-1-i; j++) {
            if (arr[j].compareTo(arr[j+1])>0){
                swap(arr,j,j+1);
                lastSwappedIndex = j+1;  //最后一次交换位置
            }
        }
        i = arr.length - lastSwappedIndex;   // 还要交换的元素数量
    }
}
```

