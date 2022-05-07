/**
 * @author wanyu
 * @Classname SelectionSort
 * @Date 2021/11/2 10:54
 */
public class SelectionSort {
    public static <E extends Comparable<E>> void sort(E[] arr){
        for (int i = 0; i < arr.length; i++) {
            //寻找[i,n)区间里的最小值
            int minIndex = i;    //最小值的索引为i
            for (int j = i+1; j < arr.length; j++)   //从i的下一个数开始
                //如果找到一个比第i个数小的数，就把他所在的索引记为当前轮次的最小值
                if (arr[j].compareTo(arr[minIndex])<0)
                    minIndex = j;
            if(i != minIndex)//比较索引即可，无需比较具体数据，减少交换次数，优化不大
                swap(arr,i,minIndex);  //将最小值交换到第i个数处
        }
    }

    private static <E> void swap(E[] arr,int i,int j){
        E t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    public static void main(String[] args) {
        //简单数组测试
        Integer[] arr = {1,4,2,3,6,5};
        SelectionSort.sort(arr);
        for (int e:arr)
            System.out.print(e+" ");
        System.out.println();

        //生成随机数组测试
        int[] dataSize = {10000,100000};
        for(int n:dataSize){
            Integer[] arr1 = ArrayGenerator.generateRandomArray(n,n);
            SortingHelper.sortTest("SelectionSort",arr1);
        }
    }
}
