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

**快排的不稳定分析：**

假设待排序数组: `a = [ 1, 2, 2, 3, 4, 5, 6 ];`

在快速排序的随机选择比较子(即pivot)阶段：

若选择a[2]（即数组中的第二个2）为比较子，而把大于等于比较子的数均放置在大数数组中，则a[1]（即数组中的第一个2）会到pivot的右边， 那么数组中的两个2非原序（这就是“不稳定”）。

若选择 a[1] （即数组中的第一个2）为比较子，而把小于等于比较子的数均放置在小数数组中，则数组中的两个 2 顺序也非原序 。

这就说明，quick sort是不稳定的。



**快排的总结与复杂度分析：**

在学完随机化快排、双路快排和三路快排后，对快排的改进思路及其复杂度应该有一定的分析。

最初始的快排版本助记如下图，将小于和大于部分都放在左边，使用双指针i和j，i放在for循环中，不单独体现

![image-20220215231243252](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/%E5%BF%AB%E6%8E%92%E6%9C%80%E5%88%9D%E7%89%88%E6%9C%AC%E5%8A%A9%E8%AE%B0%E5%9B%BE.png)

最初始的版本，没有随机化基准值，存在“能找到一组数据，让算法100%恶化”，即对于近乎有序的数组，其时间复杂度变为O(n^2) ，这里的O(n^2) 显然是最坏的情况，因为对于“能找到一组数据，让算法100%恶化”，就应该去看它的最坏情况，因为这样的数据很容易能找到，即**近乎有序的数组**，而一旦用到这些数据，算法的复杂度我们是不能忍受的。

后面使用了随机化快排，这个随机化快排从某种角度上说是一种随机算法，因为其每次选定的基准值是不同的，那么分析复杂度时，是应该用最坏情况，还是期望情况。答案仍然是看最坏情况，因为仍然存在“能找到一组数据，让算法100%恶化”，即对于**大量重复数据的数组**，随机化快排退化成了O(n^2)。这样的数据依然很好找。

为了解决这个问题使用了双路快排，把=v的元素放在数组的两端，解决分布不平衡问题，使用双指针 i 和 j ，相向推进直至 i >= j

![image-20220215232733122](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/%E5%8F%8C%E8%B7%AF%E5%BF%AB%E6%8E%92%E5%8A%A9%E8%AE%B0%E5%9B%BE2.png)

这时计算复杂度是应该用最坏情况，还是期望情况。答案是应该用期望情况，因为“没有一组数组，能让算法100%恶化”，理论上来讲可能会存在这样数组，但概率非常非常低，因此考虑最坏情况是没有意义的，所以此时复杂度为O(nlogn)，为期望复杂度。

三路快速排序是双路快速排序的进一步改进版本，对处理**大量重复元素**的数组非常有效，等于 v 的数据在下次递归中不再需要排序。用三个指针辅助标记。时间复杂度分析同双路快排，如果都是重复元素，时间复杂度为O(n)级别

![image-20220215232900381](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/%E4%B8%89%E8%B7%AF%E5%BF%AB%E6%8E%92%E5%8A%A9%E8%AE%B0%E5%9B%BE.png)

综上所述，考虑复杂度是最坏情况还是期望情况，因该去想考虑最坏情况有没有意义，如果有数据让最坏情况很容易出现，那么就必须用最坏情况计算，否则最坏情况就没意义，而使用期望情况





## 三、过程图示

![QuickSort](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/QuickSort.png)



## 四、实例代码

```java
// 对arr[l...r]部分进行partition操作
// 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
public class QuickSort {

    public static <E extends Comparable<E>> void sort(E[] arr){
        sort(arr,0,arr.length-1);
    }

    public static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
            if (l>=r) return;

            int p = partition(arr,l,r);  // 返回索引值
            sort(arr,l,p-1);  // 注意分界点
            sort(arr,p+1,r);
    }


        private static <E extends Comparable<E>> int partition(E[] arr, int l, int  r){
        // 指定最左端元素为基准值
        int j=l;
        // i指向当前索引元素，j指向小于arr[l]区域的最后一个元素，脑子里要有图
        // 从l的下一个开始for循环，arr[i] > arr[l] 时，让 i++ 就可以了，相当于不用管
        for (int i = l+1; i <= r; i++) {
            // 如果当前元素小于基准值，应该交换arr[i]和arr[j+1]，随后j++，这样arr[i]就放到了<v的部分
            if (arr[i].compareTo(arr[l])<0){
                //先让j+1，指向小于arr[l]的区域后面一个元素，再交换
//                swap(arr,i,j+1);
//                j++;

                //或者先+1，再交换
//                j++;
//                swap(arr,i,j);

                // 以上两种都可以合写为:
                 swap(arr,i,++j);
            }
        }
        swap(arr,l,j);
        return j;
    }

    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}
```





## 五、优化

### 优化一：避免递归到底

```java
public static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
    // if (l>=r) return;
    // 优化一：避免递归到底
    if (r - l <= 15){
        InsertionSort.sort(arr,l,r);
        return;
    }

    int p = partition(arr,l,r);  // 返回索引值
    sort(arr,l,p-1);  // 注意分界点
    sort(arr,p+1,r);
}
```



### 优化二：随机化快排--解决近乎有序的数组

在**近乎有序的数组**中，初始的快排非常慢，因为前面partition操作的基数选择了最左侧的数，其在近乎有序的数组中递归时分界点大概率都是最左侧，递归树的高度就成了n（上一节的归并排序递归深度为logn），导致其变成近乎O(n^2)的复杂度。优化方法为使用**随机化快排**，即随机挑选基准值

虽然最坏情况的时间复杂度仍然为O(n^2)，但是这种概率非常小（因为每次都能随机到最小的数字的概率很小），随机化快排的期望时间复杂度则是O(nlogn)

优化后虽然还是没有归并快（归并使用了优化，近乎有序的数组不用归并过程），但在可以接受的范围内。

```java
private static <E extends Comparable<E>> int partition(E[] arr, int l, int  r){
    // 优化二：随机指定基准值
    // nextInt函数是[0，n)随机值，所以这里应该传入r-l+1。其实传入r-l也不太影响结果，但r-l+1更符合随机抽取数组值的逻辑。
    // 这里还有个随机操作上的小优化，即不让每次partition都创建一个Random对象，而是在最上面的sort函数中创建，然后通过函数参数依次传进partition中。限于篇幅此处略过。

    int p = l + (new Random()).nextInt(r-l+1);
    swap(arr,l,p);

    int j=l;
    // i指向当前索引元素，j指向小于arr[l]区域的最后一个元素，脑子里要有图
    // 从l的下一个开始for循环，arr[i] > arr[l] 时，让 i++ 就可以了，相当于不用管
    for (int i = l+1; i <= r; i++) {
        // 如果当前元素小于基准值，应该交换arr[i]和arr[j+1]，随后j++，这样arr[i]就放到了<v的部分
        if (arr[i].compareTo(arr[l])<0){
            swap(arr,i,j+1);
            j++;
        }
    }
    swap(arr,l,j);
    return j;
}
```

### 优化三：双路快排--解决大量重复元素的数组

当测试数组包含**大量相同元素**，快速排序算法再次退化成了O(n^2) 级别的算法，因为=v的数据太多，不管是放在>v的区域还是<v的区域，都会造成数组分布极度不平衡，递归树长度变为n，所以时间复杂度退化成了O(n^2)，解决的方法是使用**双路快排**

即将**<v**和**>v**由之前的放在数组的左端，改为放到数组的两端，需要使用两个索引值（i、j）用来遍历我们的序列，将 **<=v** 的元素放在索引 i 所指向位置的左边，而将 **>=v** 的元素放在索引 j 所指向位置的右边，平衡左右两边子数组（说白了就是把=v的元素分散开来放）

![QuickSort2Ways](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/QuickSort2Ways.png)

```java
private static <E extends Comparable<E>> int partition(E[] arr, int l, int  r){
    int p = l + (new Random()).nextInt(r-l+1);
    swap(arr,l,p);

    // 优化三：双路快速排序
    // 使得arr[l+1...i) <= v; arr(j...r] >= v，把等于基准值的数尽量均匀分布在两个部分，不会造成不平衡的情况
    // 定义两个索引分别指向：<v区域的下一位 和 >v区域的前一位
    int i =l+1, j=r;
    while (true){
        // 下面两个while判定中arr[i]不能包含 = arr[l]，因为其中任意一个判定=成功，都会把大量相同数据放置到一个半区，仍然会造成不平衡的问题
        // 即只要不碰到>=arr[l],i就+1，不碰到<=arr[l]，j就-1
        // 当i指向这个>=arr[l]的数，j指向这个<=arr[l]的数，然后交换他们，如果是与arr[l]相等的数交换到了另一边，这样才能尽量均匀分布在两侧
        while (i<=j && arr[i].compareTo(arr[l])<0) i++;
        while (i<=j && arr[j].compareTo(arr[l])>0) j--;
        // 如果i>=j，则是越界，停止循环
        if (i>=j) break;
        swap(arr,i,j);
        // 交换完还是要继续移动双指针
        i++;
        j--;
    }
    // 务必注意！遍历结束后，i指向从前往后看第一个>=arr[l]的位置，j指向从后往前看，最后一个<=arr[l]的位置，
    // 现在标定点是在<=arr[l]这一端，所以交换arr[l]和arr[j]，它们都是<=v区域的值，而不是交换l和i，否则会排序失败
    swap(arr,l,j);
    return j;
}
```

### 优化四：三路快排--进一步解决大量重复元素的数组

三路快速排序是双路快速排序的进一步改进版本，对处理**大量重复元素**的数组非常有效。三路排序算法把排序的数据分为三部分，分别为小于 v，等于 v，大于 v，v 为标定值，这样三部分的数据中，**等于 v **的数据在下次递归中**不再需要排序**，小于 v 和大于 v 的数据也不会出现某一个特别多的情况，通过此方式三路快速排序算法的性能更优。

对于包含有大量重复数据的数组, 三路快排有巨大的优势,对于一般性的随机数组和近乎有序的数组, 三路快排的效率虽然不是最优的, 但是是在非常可以接受的范围里。因此, 在一些语言中, 三路快排是默认的语言库函数中使用的排序算法。比如Java

为了方便记忆，记住下图最上面的横条结构。

lt指向<v的最后一个值（初始 lt=l ），i指向当前值（初始 i = l +1 ），gt指向>v的第一个值 (初始 gt = r +1)

![QuickSort3Ways](https://jswanyu-1309100582.cos.ap-shanghai.myqcloud.com/picgo/QuickSort3Ways.png)

```Java
public static <E extends Comparable<E>> void sort(E[] arr){
    sort(arr,0,arr.length-1);
}

private static <E extends Comparable<E>> void sort(E[] arr, int l, int r) {
    if (r - l <= 15){
        InsertionSort.sort(arr,l,r);
        return;
    }
    // 随机化基准值
    int p = l + (new Random()).nextInt(r-l+1);
    swap(arr,l,p);

    // 希望将数组分成三部分：arr[l+1,lt]<v,arr[lt+1,i-1]=v,arr[gt,r]>v,脑子里要有图，或者拿纸笔写
    // 确定初始值要让每个区间最开始都为空区间，所以lt为l,gt为r+1。lt(less than),gt(greater than)
    int lt = l, i = l+1, gt = r+1;
    while (i < gt){
        if (arr[i].compareTo(arr[l])<0){
            swap(arr,i,lt+1);
            lt++;
            // 上面两句可以合并为swap(arr,i,++lt);
            i++;
        }
        else if (arr[i].compareTo(arr[l])>0){
            // 注意此时不用i++，因为gt先-1，换过来的值也是未处理过的
            swap(arr,i,gt-1);
            gt--;
            // 上面两句可以合并为swap(arr,i,--gt);
        }
        else{ // arr[i] = arr[l]
            i++;
        }
    }
    // 因为目前lt位置是小于arr[l]的，所以交换之后，最左边还是小于arr[l]，arr[lt]=arr[l]
    swap(arr,l,lt);

    // 交换完之后，arr[l,lt-1]<v,arr[lt,gt-1]=v,arr[gt,r]>v，再递归
    sort(arr,l,lt-1);
    sort(arr,gt,r);
}
```

