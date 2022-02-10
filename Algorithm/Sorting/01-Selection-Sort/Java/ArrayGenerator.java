import java.util.Random;

/**
 * @author wanyu
 * @Classname ArrayGenerator
 * @Date 2021/11/2 10:52
 */
public class ArrayGenerator {

    private ArrayGenerator(){}

    // 生成一个长度为n的有序数组
    public static Integer[] generateOrderArray(int n){
        Integer[] arr = new Integer[n];
        for (int i = 0; i < n; i++)
            arr[i] = i;
        return arr;
    }

    // 生成一个长度为n的随机数组，每个数字的范围是[0,bound)
    public static Integer[] generateRandomArray(int n,int bound){
        Integer[] arr = new Integer[n];
        Random rnd = new Random();
        for (int i = 0; i < n; i++) {
            arr[i] = rnd.nextInt(bound);
        }
        return arr;
    }


}
