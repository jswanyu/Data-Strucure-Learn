import java.util.Arrays;

/**
 * @Classname: MergeSort
 * @author: wanyu
 * @Date: 2021/11/30 16:56
 */
public class MergeSort {
    private MergeSort(){}

    // sort为优化后的最终版本，初始版本放在下面的sort2中。
    public static <E extends Comparable<E>> void sort(E[] arr){
        //优化3：在一开始开辟数组空间，而不是在每次的merge中开辟空间
        E[] temp = Arrays.copyOf(arr,arr.length);
        sort(arr,0,arr.length-1, temp);
    }

    public static <E extends Comparable<E>> void sort(E[] arr, int l, int r, E[] temp){
        //优化1: 对于小规模数组, 使用插入排序，避免递归到底
        if (r-l<=15){
            InsertionSort.sort(arr, l, r);  //需要将之前[0,n]数组的插入排序改写为[l,r]的
            return;
        }

        int mid = l+(r-l)/2;
        sort(arr,l,mid,temp);
        sort(arr,mid+1,r,temp);

        // 优化2: 对于arr[mid] <= arr[mid+1]的情况，这种情况左半区恒小于右半区，不需要进行merge
        // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
        if (arr[mid].compareTo(arr[mid+1])>0)
            merge(arr,l,mid,r,temp);
    }

    private static <E extends Comparable<E>> void merge(E[] arr, int l, int mid, int r, E[] temp){
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
            else if(temp[i].compareTo(temp[j])<=0){
                arr[k] = temp[i]; i++;
            }
            else{
                arr[k] = temp[j]; j++;
            }
        }
    }



/************************************************** 初始版本 *********************************************************************/
    public static <E extends Comparable<E>> void sort2(E[] arr){
        sort2(arr,0,arr.length-1);
    }

    // 递归使用归并排序，对arr[l...r]的范围进行排序，l是第一个元素的位置，r是最后一个元素的位置，两边都是闭区间
    // 所以这种情况下，在递归调用长度为n的数组时，l就是数组的下标位置0，r就是数组的下标位置n-1
    public static <E extends Comparable<E>> void sort2(E[] arr, int l, int r){
        if (l>=r) return; // 只有1个元素或者没有元素

        int mid = l+(r-l)/2; // 防止整型计算溢出，亿级数据量才用到
        sort2(arr,l,mid);
        sort2(arr,mid+1,r);

        if (arr[mid].compareTo(arr[mid+1])>0)
            merge2(arr,l,mid,r);
    }

    // 合并两个有序的区间，arr[l,mid] 和arr[mid+1,r]
    private static <E extends Comparable<E>> void merge2(E[] arr, int l, int mid, int r){
        // copyOfRange方法是不包括右端点的，所以要r+1。
        // 这里注意arr是从l开始索引的，但temp是从0开始索引的，所以相比于arr，temp有一个l的偏移量
        E[] temp = Arrays.copyOfRange(arr,l,r+1);
        //定义两个指针分别指向左右半区的首位置
        int i = l, j = mid+1;
        for (int k = l; k <= r; k++) {
            //先判断越界问题：
            if (i>mid){//如果左边的指针已经大于mid，说明左半区已经都排序完，把右半区剩下的数字放入arr，temp数组偏移量为l。
                arr[k] = temp[j-l]; j++;
            }
            else if(j>r){//如果右边的指针已经大于r，说明右半区已经都排序完，把左半区剩下的数字放入arr，temp数组偏移量为l。
                arr[k] = temp[i-l]; i++;
            }
            // 再判断两个半区的大小：
            else if(temp[i-l].compareTo(temp[j-l])<=0){  // 左半部分所指元素 <= 右半部分所指元素
                arr[k] = temp[i-l]; i++;
            }
            else{// 左半部分所指元素 > 右半部分所指元素
                arr[k] = temp[j-l]; j++;
            }
        }
    }





    public static void main(String[] args) {
        int[] dataSize = {100000};
        for(int n:dataSize) {
            //随机数组
            System.out.println("Random Array:");
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("InsertionSort", arr2);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("MergeSort2", arr);
            System.out.println();

            //有序数组
            System.out.println("Ordered Array:");
            arr = ArrayGenerator.generateOrderArray(n);
            arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("InsertionSort", arr2);
            SortingHelper.sortTest("MergeSort", arr);
            SortingHelper.sortTest("MergeSort2", arr);
            System.out.println();
        }
    }
}


