# 插入排序

## 一、概念及其介绍
插入排序(InsertionSort)，一般也被称为直接插入排序。基本思想是每一次将一个元素 **插入** 到它前面的有序数组中



## 二、适用说明

|   算法   | 最好时间 | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :------: | :------: | :------: | :------: | :----: |
| 插入排序 |  O(n）   |  O(n^2)  |  O(n^2)  |   O(1)   |  稳定  |

**优点**就是数据有序的情况下，可以提前终止部分内层循环，只在有需要时才对数组进行排序

**缺点**就是所有比插入元素大的元素都必须移动

最优的情况是当待排序数组是有序时，只需当前数跟前一个数比较一下就可以了，这时一共需要比较 **N-1** 次，时间复杂度为 **O(N)**。这具有非常重要的意义，因为**日常有时候的数据就是近乎有序的**

最坏的情况是待排序数组是逆序的，此时需要比较次数最多，最坏的情况是 **O(n^2)**。

对于随机顺序的数组来说，移动和比较的次数与最坏情况接近，也就是说 当数组大小加倍时，一般都需要付出4倍的努力来排序。



## 三、过程图示

插入排序是每一次将一个元素 **插入** 到它前面的有序数组中。实际上有两种插入的方式：

- 逐个交换：待插入元素逐个交换到前面

    <img src="https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/DataStructure%20and%20Algorithm/%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F-%E5%9B%BE%E7%A4%BA.gif" alt="img" style="zoom:150%;" />

- 先暂存再后移：先暂存待插入元素，然后前面比暂存元素严格大的后移（放到优化一部分讲）

    <img src="https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/DataStructure%20and%20Algorithm/%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F-%E5%9B%BE%E7%A4%BA1.gif" alt="img" style="zoom:150%;" />



## 四、实例代码

第0个数不动，从第1个数开始把 nums[i] 插入有序数组 nums[0..i - 1]

每次判定元素逆序成功就swap()，相当于插了多次。在动图中即表现为红色的临时值一直在插入，再取出来，再插入。

```Java
public class InsertionSort {    
	public static <E extends Comparable<E>> void sort2(E[] arr){
        // 把 nums[i] 插入有序数组 nums[0..i - 1]，从nums[1]开始，nums[0]不用动
        for (int i = 1; i < arr.length; i++) {
            // 有索引j-1，j不能为0
            for (int j = i; j > 0 && arr[j].compareTo(arr[j-1])<0; j--)
                swap(arr,j,j-1);
        }
    }
   
    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```



## 五、优化

优化一：减少插入次数，先暂存待插入元素，然后前面比暂存元素严格大的后移

![insertionSort](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/insertionSort%E7%A4%BA%E6%84%8F%E5%9B%BE.gif)

判定当前元素比前一个元素大，那就让前一个元素后移，不用让arr[j]与arr[j-1]一直交换，等到找到合适的插入位置，只插一次

```java
public static <E extends Comparable<E>> void sort(E[] arr){
    for (int i = 1; i < arr.length; i++) {
        E e = arr[i];  //复制一份外层循环当前轮次的元素
        int j;         //变量j保存元素e应该所在的位置，单独初始化是因为for循环后面还要用到
        // 注意是当前轮次的值arr[i]即e与arr[j-1]比较，而不是arr[j]，当前轮次的arr[j]就是e，自然要跟前一个数字相比
        // 这轮for循环的功能：1、找到当前轮次的元素应该放的位置 2、将大的元素后移
        for (j = i; j>0 && e.compareTo(arr[j-1])<0; j--)
            arr[j] = arr[j-1]; //比前一个元素大，那就让前一个元素后移，不用让arr[j]与arr[j-1]一直交换
        arr[j] = e;    //此时j就是合适的位置，将当前轮次的e赋给它
    }
    
    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```



### 二分查找法改进

查找插入的位置可以使用二分查找法，但仍然需要后移比插入元素大的元素，所以时间复杂度不变

不要求掌握



## 六、插入排序的重要意义

插入排序有个特点非常重要：插入排序的内存循环有一定机会可以提前终止，这样就能让：**数据接近有序的时候，插入排序可以很快完成。**「接近有序」的意思是：每个元素和它排序以后最终所在的位置不远。这一点需要和「选择排序」进行比较。

![image-20220506230904374](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/DataStructure%20and%20Algorithm/%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F%E5%AF%B9%E6%AF%94%E9%80%89%E6%8B%A9%E6%8E%92%E5%BA%8F.png)

**在数组「几乎有序」的前提下，插入排序的时间复杂度可以达到 O(N)**，因此「插入排序」可以作为高级排序算法的一个子过程（后面在归并排序和快速排序算法里我们会看到）。

> 这里注意冒泡排序在有序数组的情况下，也能做到时间复杂度为O(N)，如果有一轮循环没有交换，可以提前结束，但这种情况比较少出现，很可能只能减少最后几轮循环，优化效果不明显

由于「插入排序」在「几乎有序」的数组上表现良好，特别地，在「短数组」上的表现也很好。因为「短数组」的特点是：每个元素离它最终排定的位置都不会太远。因此**在小区间内执行排序任务的时候，可以转向使用「插入排序」。**

综合来看，一般同样一个排序任务，插入排序会比选择排序和冒泡排序时间花费的更少



