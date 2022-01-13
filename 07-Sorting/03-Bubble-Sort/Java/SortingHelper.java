/**
 * @author wanyu
 * @Classname SortingHelper
 * @Date 2021/11/2 10:53
 */
public class SortingHelper {
    private SortingHelper(){}

    public static <E extends Comparable<E>> boolean isSorted(E[] arr){
        for (int i = 1; i < arr.length; i++)
            if (arr[i-1].compareTo(arr[i])>0)
                return false;
        return true;
    }

    public static <E extends Comparable<E>> void sortTest(String sortname, E[] arr){
        long startTime = System.nanoTime();
        //后续改成反射
        if (sortname.equals("SelectionSort"))
            SelectionSort.sort(arr);
        else if (sortname.equals("InsertionSort"))
            InsertionSort.sort(arr);
        else if (sortname.equals("BubbleSort"))
            BubbleSort.sort(arr);

        long endTime = System.nanoTime();
        double time = (endTime - startTime) / 1000000000.0;

        if (!SortingHelper.isSorted(arr))
            throw new RuntimeException("SelectionSort failed");
        System.out.println(String.format("%s, n=%d : %f s",sortname,arr.length,time));
    }
}