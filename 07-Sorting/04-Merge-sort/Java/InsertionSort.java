/**
 * @author wanyu
 * @Classname InsertionSort
 * @Date 2021/11/2 10:52
 */
import java.util.Arrays;

public class InsertionSort {
    // 优化:减少当前轮次arr[i]的交换次数，找到合适的插入位置，只插一次
    // 将其作为sort，未优化的作为sort2。sort2中每次判定成功就swap()，相当于插了多次
    public static <E extends Comparable<E>> void sort(E[] arr){
        for (int i = 0; i < arr.length; i++) {
            E t = arr[i];  //复制一份外层循环当前轮次的元素
            int j;         //变量j保存元素e应该所在的位置，单独初始化是因为for循环后面还要用到
            // 务必注意是当前轮次的值arr[i]即t与arr[j-1]比较，而不是arr[j]
            for (j = i; j-1 >=0 && t.compareTo(arr[j-1])<0; j--)
                arr[j] = arr[j-1]; //比前一个元素大，那就让前一个元素后移，不用让arr[j]与arr[j-1]一直交换
            arr[j] = t;    //此时j就是合适的位置，将开始的arr[i]赋给它
        }
    }

    //对[l,r]区间的元素进行插入排序
    public static <E extends Comparable<E>> void sort(E[] arr, int l, int r){
        //注意这里是<=r
        for (int i = l; i <= r; i++) {
            E t = arr[i];  //复制一份外层循环当前轮次的元素
            int j;         //变量j保存元素e应该所在的位置，单独初始化是因为for循环后面还要用到
            // 务必注意是当前轮次的值arr[i]即t与arr[j-1]比较，而不是arr[j]
            for (j = i; j-1 >=l && t.compareTo(arr[j-1])<0; j--)
                arr[j] = arr[j-1]; //比前一个元素大，那就让前一个元素后移，不用让arr[j]与arr[j-1]一直交换
            arr[j] = t;    //此时j就是合适的位置，将开始的arr[i]赋给它
        }
    }


    //旧写法作为sort2，以后不再使用
    public static <E extends Comparable<E>> void sort2(E[] arr){
        for (int i = 0; i < arr.length; i++) {
            //将arr[i]插入到合适的位置，初始指向arr[i]位置，每一次去比较它和前面一个元素的大小，因此是j-1>=0
//            for (int j = i; j-1 >= 0; j--) {
//                if (arr[j].compareTo(arr[j-1])<0)
//                    swap(arr,j,j-1);
//                else break;
//            }
            //另一种写法
            for (int j = i; j-1 >= 0 && arr[j].compareTo(arr[j-1])<0; j--)
                swap(arr,j,j-1);
        }
    }


    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    public static void main(String[] args) {
        int[] dataSize = {10000,100000};
        for(int n:dataSize) {
            //随机数组
            System.out.println("Random Array:");
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("InsertionSort", arr);
            SortingHelper.sortTest("SelectionSort", arr2);
            System.out.println();

            //有序数组
            System.out.println("Ordered Array:");
            arr = ArrayGenerator.generateOrderArray(n);
            arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("InsertionSort", arr);
            SortingHelper.sortTest("SelectionSort", arr2);
            System.out.println();
        }
    }
}
