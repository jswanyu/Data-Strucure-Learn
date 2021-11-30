import java.util.Arrays;

/**
 * @Classname: BubbleSort
 * @author: wanyu
 * @Date: 2021/11/30 15:23
 */
public class BubbleSort {
    private BubbleSort(){}

    public static <E extends Comparable<E>> void sort(E[] arr){
        //设置一个标志，如果这一趟发生了交换，则为true，否则为false。如果有一趟没有发生交换，说明排序已经完成
        boolean flag = true;  //第一次判断时标志位为true
        //外层循环需要flag为true
        for (int i = 0; i < arr.length-1 && flag; i++) {
            //每次的内层循环将标志位设为假，否则没意义
            flag = false;
            //内层循环会执行到底
            for (int j = 0; j < arr.length-1-i; j++) {
                if (arr[j].compareTo(arr[j+1])>0){
                    swap(arr,j,j+1);
                    flag = true;
                }
            }
        }
    }



    public static <E extends Comparable<E>> void sort2(E[] arr){
        //对于n个数，要进行n-1轮循环，每一轮将最大的数冒到最后面去
        for (int i = 0; i < arr.length-1; i++) {
            //n个数中，相邻的元素就有n-1组，第0轮要比较n-1次，第i轮要比较n-1-i
            for (int j = 0; j < arr.length-1-i; j++) {
                if (arr[j].compareTo(arr[j+1])>0)
                    swap(arr,j,j+1);
            }
        }
    }



    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    public static void main(String[] args) {
        int[] dataSize = {100000};
        for(int n:dataSize) {
            //随机数组
            System.out.println("Random Array:");
            Integer[] arr = ArrayGenerator.generateRandomArray(n, n);
            Integer[] arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("BubbleSort", arr);
            SortingHelper.sortTest("InsertionSort", arr2);
            System.out.println();

            //有序数组
            System.out.println("Ordered Array:");
            arr = ArrayGenerator.generateOrderArray(n);
            arr2 = Arrays.copyOf(arr,arr.length);
            SortingHelper.sortTest("BubbleSort", arr);
            SortingHelper.sortTest("InsertionSort", arr2);
            System.out.println();
        }
    }



}
