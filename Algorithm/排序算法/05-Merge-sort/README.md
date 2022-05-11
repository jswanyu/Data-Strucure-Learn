# 归并排序

## 一、概念及其介绍

归并排序（Merge sort）是建立在归并操作上的一种有效、稳定的排序算法，该算法是采用分治法(Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。

作为一种典型的分而治之思想的算法应用，归并排序的实现有下面这些方法：

- 自上而下的递归（所有递归的方法都可以用迭代重写，所以就有了第 2 种方法）；
- 自下而上的迭代；
- 原地归并排序；

主要学习第一种，用递归理解分治的思想，这是最好理解、最通用的归并。后面二三种学有余力可以学习



### 算法步骤

1. 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列；
2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置；
3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置；
4. 重复步骤 3 直到某一指针达到序列尾；
5. 将另一序列剩下的所有元素直接复制到合并序列尾。



## 二、算法性能

|   算法   | 最好时间 | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :------: | :------: | :------: | :------: | :----: |
| 归并排序 |  O(n）   | O(nlogn) | O(nlogn) |   O(n)   |  稳定  |

归并排序的性能不受输入数据的影响，始终都是 O(nlogn) 的时间复杂度。代价是需要额外的内存空间。

归并排序适用于数据量大，并且对稳定性有要求的场景



## 三、过程图示

归并过程：不断比较temp[i]和temp[j]的大小，找到合适的位置放到原数组中

![image-20220213153723211](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E4%B8%8E%E7%AE%97%E6%B3%95-%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F%E5%9B%BE.png)



动图演示：

![mergeSort](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/mergeSort%E7%A4%BA%E6%84%8F%E5%9B%BE.gif)





## 四、实例代码

利用递归进行自顶向下的归并排序

```java
public class MergeSort {
    private MergeSort(){}

    public static <E extends Comparable<E>> void sort(E[] arr){
        sort(arr,0,arr.length-1);
    }

    // 递归使用归并排序，对arr[l...r]的范围进行排序，l是第一个元素的位置，r是最后一个元素的位置，两边都是闭区间
    // 所以这种情况下，在递归调用长度为n的数组时，l就是数组的下标位置0，r就是数组的下标位置n-1
    public static <E extends Comparable<E>> void sort(E[] arr, int l, int r){
        if (l>=r) return; // 只有1个元素或者没有元素
        int mid = l+(r-l)/2; // 防止整型计算溢出，亿级数据量才用到
        sort(arr,l,mid);
        sort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }

    // 合并两个有序的区间，arr[l,mid] 和arr[mid+1,r]
    private static <E extends Comparable<E>> void merge(E[] arr, int l, int mid, int r){
        // copyOfRange方法是不包括右端点的，所以要r+1。
        // 即写copyOfRange(arr,0,5)它是不复制arr[5]这个数的，要写成copyOfRange(arr,0,6)
        // 这里注意arr是从l开始索引的，但temp是从0开始索引的，所以相比于arr，temp有一个l的偏移量
        E[] temp = Arrays.copyOfRange(arr,l,r+1);
        //定义两个指针分别指向左右半区的首位置
        int i = l, j = mid+1;
        for (int k = l; k <= r; k++) {
            //先判断越界问题：
            //如果左边的指针已经大于mid，说明左半区已经都排序完，把右半区剩下的数字放入arr，temp数组偏移量为l。
            if (i>mid){
                arr[k] = temp[j-l]; j++;
            }
            //如果右边的指针已经大于r，说明右半区已经都排序完，把左半区剩下的数字放入arr，temp数组偏移量为l。
            else if(j>r){
                arr[k] = temp[i-l]; i++;
            }
            // 再判断两个半区的大小：
            // 注意是temp[i-l]和temp[j-l]比较，容易忘记偏移量l
            // 记住这里是小于等于，在有些问题中等号很重要，比如剑指51：逆序对
            // 并且写成 < 就丢失了稳定性（相同元素原来靠前的排序以后依然靠前）
            else if(temp[i-l].compareTo(temp[j-l])<=0){  // 左半部分所指元素 <= 右半部分所指元素
                arr[k] = temp[i-l]; i++;
            }
            else{// 左半部分所指元素 > 右半部分所指元素
                arr[k] = temp[j-l]; j++;
            }
        }
    }
}
```





## 五、优化

### 优化一：对于小规模数组, 使用插入排序，避免递归到底

数组元素较少且是有序的情况，插入排序复杂度可能到O(n)级别

```c++
public class MergeSort {    
	public static <E extends Comparable<E>> void sort(E[] arr, int l, int r){
        //if (l>=r) return; // 只有1个元素或者没有元素
        
        // 优化1: 对于小规模数组, 使用插入排序，避免递归到底
        if (r-l<=15){
            InsertionSort.sort(arr, l, r);  //需要将之前[0,n]数组的插入排序改写为[l,r]的
            return;
        }
            
        int mid = l+(r-l)/2; // 防止整型计算溢出，亿级数据量才用到
        sort(arr,l,mid);
        sort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
}
```



### 优化二：对于左半区和右半区整体大小已经确定的情况可以不用再进行递归

对于arr[mid] <= arr[mid+1]的情况,不进行merge ，因为归并过程保证了l~mid是有序的，mid+1~r也是有序的，arr[mid] <= arr[mid+1]，则不用排序，这对于近乎有序的数组非常有效，会变成O(n)级别的算法。但是对于一般情况，有一定的性能损失

```c++
public class MergeSort {    
	public static <E extends Comparable<E>> void sort(E[] arr, int l, int r){
        //if (l>=r) return; // 只有1个元素或者没有元素
        
        // 优化1: 对于小规模数组, 使用插入排序，避免递归到底
        if (r-l<=15){
            InsertionSort.sort(arr, l, r);  //需要将之前[0,n]数组的插入排序改写为[l,r]的
            return;
        }
            
        int mid = l+(r-l)/2; // 防止整型计算溢出，亿级数据量才用到
        sort(arr,l,mid);
        sort(arr,mid+1,r);

        // 优化2: 对于arr[mid] <= arr[mid+1]的情况，这种情况左半区恒小于右半区，不需要进行merge
        // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
        if (arr[mid].compareTo(arr[mid+1])>0)
            merge(arr,l,mid,r);
    }
}
```



### 优化三：一开始开辟数组内存，而不是在每次merge操作中开辟

上面的代码中我们可以观察到合并操作merge()方法每次都开辟了一个数组用于复制，然后不用了再释放掉内存，然而merge的次数是比较多的，这无疑是一种浪费。因此可以在一开始sort时就开辟一个全局数组，每次递归时将这个数组传下去，用于复制数据。

```java
public class MergeSort {
    public static <E extends Comparable<E>> void sort2(E[] arr){
        //在一开始开辟数组空间，而不是在每次的merge中开辟空间。递归时将数组传下去，在合并过程中也可以不用考虑偏移量
        E[] temp = Arrays.copyOf(arr,arr.length);
        sort2(arr,0,arr.length-1, temp);
    }

    public static <E extends Comparable<E>> void sort2(E[] arr, int l, int r, E[] temp){
        if (r-l<=15){
            InsertionSort.sort(arr, l, r);
            return;
        }

        int mid = l+(r-l)/2;
        sort2(arr,l,mid,temp);
        sort2(arr,mid+1,r,temp);

        if (arr[mid].compareTo(arr[mid+1])>0)
            merge2(arr,l,mid,r,temp);
    }

    private static <E extends Comparable<E>> void merge2(E[] arr, int l, int mid, int r, E[] temp){
        // 将arr中l开始的元素依次复制到temp中l开始的位置上，复制的长度为r-l+1，这样下面就没有l的偏移量了
        System.arraycopy(arr,l,temp,l,r-l+1);

        int i = l, j = mid+1;
        for (int k = l; k <= r; k++) {
            //先判断越界问题：
            if (i>mid){
                arr[k] = temp[j]; j++;
            }
            else if(j>r){
                arr[k] = temp[i]; i++;
            }
            // 再判断两个半区的大小：
            // 注意写成 < 就丢失了稳定性（相同元素原来靠前的排序以后依然靠前）
            else if(temp[i].compareTo(temp[j])<=0){  
                arr[k] = temp[i]; i++;
            }
            else{
                arr[k] = temp[j]; j++;
            }
        }
    }
}
```







