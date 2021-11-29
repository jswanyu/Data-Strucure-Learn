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
// 对arr[l...r]部分进行partition操作
// 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
template<typename T>
int __partition(T *arr, int l, int r) {
    T v = arr[l];  //将数组最左边的数选为比较的基准

    // 下面要使得arr[ l+1 ... j ] < v ; arr[ j+1 ... i ) > v，一定要注意右半边的 i 是开区间，因为i是当前正在被检索的元素
    // 初始值j =l 的好处是最开始 i = l+1 时，左半区间为[ l+1 ... l ] ，右半区间为[ l+1 ... l +1 )，均为空区间
    // 索引 j 是指向<v部分的最后一个位置
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        //arr[i] > v 时，让 i++ 就可以了，相当于不用管
        if (arr[i] < v) {
            // j是指向<v的部分的最后一个位置，所以应该是交换arr[i]和arr[j+1]，随后j++，这样arr[i]就放到了<v的部分
            // 再随后i++，也保证了原来的arr[j+1]仍然在>v的部分
            // 下面两句可以合并为更优雅的写法：swap(arr[i], arr[++j]); //既完成交换，也完成+1
            swap(arr[i], arr[j + 1]);
            j++;
        }
    }

    swap(arr[l], arr[j]);
    return j;

}

template<typename T>
void __QuickSort(T *arr, int l, int r) {
    if (l >= r)
        return;

    int p = __partition(arr, l, r);  //返回索引值
    __QuickSort(arr, l, p - 1);      //注意分界点
    __QuickSort(arr, p + 1, r);
}

template<typename T>
void QuickSort(T *arr, int n) {
    __QuickSort(arr, 0, n - 1);
}
```



文件结构：

QuickSort.h  快速排序算法

MergeSort.h 归并排序算法

InsertionSort.h  插入排序算法

SortTestHelper.h  测试函数

main.cpp  主函数



## 五、优化

### 优化一：避免递归到底

```c++
template<typename T>
void __QuickSort(T *arr, int l, int r) {
//    if (l >= r)
//        return;
    //优化一，避免递归到底
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r);  //返回索引值
    __QuickSort(arr, l, p - 1);
    __QuickSort(arr, p + 1, r);
}
```



### 优化二：随机化快排--解决近乎有序的数组

在**近乎有序的数组**中，初始的快排非常慢，因为partition操作的基数选择了最左侧的数，其在近乎有序的数组中递归时分界点大概率都是最左侧，递归树的高度就成了n，导致其变成近乎O(n^2)的复杂度，优化方法为使用随机化快排

虽然最坏情况的时间复杂度仍然为O(n^2)，但是这种概率非常小（因为每次都能随机到最小的数字的概率很小），随机化快排的期望时间复杂度则是O(nlogn)

优化后虽然还是没有归并快（归并使用了优化，近乎有序的数组不用归并过程），但在可以接受的范围内

```c++
int __partition(T *arr, int l, int r) {

    //优化2：随机化快排：随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
    swap(arr[l],arr[rand()%(r-l+1)+l]);

    T v = arr[l]; 

    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < v) {
            swap(arr[i], arr[j + 1]);
            j++;
        }
    }

    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void __QuickSort(T *arr, int l, int r) {
    //优化一，避免递归到底
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r); 
    __QuickSort(arr, l, p - 1);
    __QuickSort(arr, p + 1, r);
}

template<typename T>
void QuickSort(T *arr, int n) {
    srand(time(NULL));   //随机化
    __QuickSort(arr, 0, n - 1);
}
```

### 优化三：双路快排--解决大量重复元素的数组

当测试数组包含**大量相同元素**，快速排序算法再次退化成了O(n^2)级别的算法，因为=v的数据太多，不管是放在>v的区域还是<v的区域，都会造成数组分布极度不平衡，递归树长度变为n，所以时间复杂度退化成了O(n^2)，解决的方法是使用**双路快排**

即将**<v**和**>v**由之前的放在数组的左端，改为放到数组的两端，需要使用两个索引值（i、j）用来遍历我们的序列，将 **<=v** 的元素放在索引 i 所指向位置的左边，而将 **>=v** 的元素放在索引 j 所指向位置的右边，平衡左右两边子数组（说白了就是把=v的元素分散开来放）

![双路快排示意图](https://github.com/wanyu416/Data-Strucure/blob/main/src/QuickSort2Ways.png)

```c++
// 双路快排返回p, 使得arr[l...p-1] <= arr[p] ; arr[p+1...r] >= arr[p]
// 即把等于标定值的数尽量均匀分布在两个部分，不会造成不平衡的情况
template<typename T>
int __partition2(T *arr, int l, int r) {
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    // 使得arr[l+1...i) <= v; arr(j...r] >= v
    // 定义两个索引分别指向：<v区域的下一位 和 >v区域的前一位
    // 这样初始化定义i，j，两个初始区间就都是空的
    int i=l+1,j=r;
    while(1){
        // 越界问题：i是不能比r大的，而j是不能小于l+1的，因为l是标定点
        // while判定中arr[i]不能是<=v，arr[j]不能是>=v，因为其中任意一个判定=成功，都会把大量相同数据放置到一个半区，
        // 仍然会造成不平衡的问题，而不是等于也很好理解，i指向这个>=v的数，j指向这个<=v的数，然后交换他们，与v相等的数交换到了另一边，
        // 随后i++，j--，跳过这个交换过来的数，不管他等不等于v，进行后面元素的判定
        while(i<=r && arr[i]<v) i++;
        while(j>=l+1 && arr[j]>v) j--;
        if(i>j) break;
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    // 遍历结束后，i指向从前往后看第一个>=v的位置，j指向从后往前看，最后一个<=v的位置，
    // 现在标定点是在<=v这一端，所以交换arr[l]和arr[j]，它们都是<=v区域的值
    swap(arr[l],arr[j]);

    return j;
}


template<typename T>
void __QuickSort2(T *arr, int l, int r) {
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition2(arr, l, r);
    __QuickSort2(arr, l, p - 1);
    __QuickSort2(arr, p + 1, r);
}


template<typename T>
void QuickSort2(T *arr, int n) {
    srand(time(NULL));
    __QuickSort2(arr, 0, n - 1);
}
```

### 优化四：三路快排--进一步解决大量重复元素的数组

三路快速排序是双路快速排序的进一步改进版本，对处理大量重复元素的数组非常有效。三路排序算法把排序的数据分为三部分，分别为小于 v，等于 v，大于 v，v 为标定值，这样三部分的数据中，**等于 v **的数据在下次递归中**不再需要排序**，小于 v 和大于 v 的数据也不会出现某一个特别多的情况，通过此方式三路快速排序算法的性能更优。

对于包含有大量重复数据的数组, 三路快排有巨大的优势,对于一般性的随机数组和近乎有序的数组, 三路快排的效率虽然不是最优的, 但是是在非常可以接受的范围里。因此, 在一些语言中, 三路快排是默认的语言库函数中使用的排序算法。比如Java



![三路快排示意图](https://github.com/wanyu416/Data-Strucure/blob/main/src/QuickSort3Ways.png)

```c++
//将arr[l...r]分为<v;==v;>v 三部分
//之后递归对<v;>v两部分进行三路快排
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
    if(r-l<=15){
        InsertionSort(arr,l,r);
        return;
    }

    //partition
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    int lt = l;    //arr[l+1...lt]<v, lt指向<v的最后一位, lt(less than)
    int gt = r+1;  //arr[gt...r]>v    gt指向>v的第一位, gt(greater than)
    int i = l+1;   //arr[l+1...i)==v  i指向待处理的元素

    while(i<gt){
        if(arr[i]<v){
            swap(arr[i],arr[lt+1]);
            lt++;
            i++;
        }
        else if(arr[i]>v){
            swap(arr[i],arr[gt-1]);
            gt--; //这里不需要进行i++，i指向交换过来的arr[gt-1]，这仍然是个未判断的值
        }
        else{//arr[i]==v
            i++;
        }
    }
    swap(arr[l],arr[lt]);  //arr[l]是等于v的，放在arr[lt]处，随后递归lt之前的部分，即lt-1

    // c++不方便返回一个区间的数，因此直接递归，不编写专门的partition函数
    __quickSort3Ways(arr,l,lt-1);  //这里容易出错，是递归lt之前的部分，即lt-1
    __quickSort3Ways(arr,gt,r);
}

template<typename T>
void quickSort3Ways(T arr[],int n){
    srand(time(NULL));
    __quickSort3Ways(arr,0,n-1);
}
```

