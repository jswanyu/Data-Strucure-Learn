# 希尔排序

希尔排序的理论有一定难度，不感兴趣的朋友不需要深入研究；



希尔排序是插入排序的优化，利用的是插入排序的重要意义：在小数组（几乎有序的数组）上表现良好；通过**分组插入排序**使得数组变得逐步有序；最后一轮执行标准的插入排序



## 希尔排序的基本思想

希尔排序的基本思想：开始的时候逐渐让数组变得基本有序，最后使用一次使用「插入排序」就变得高效了。

- 「逐渐让数组变得基本有序」的方法是让移动的「步幅」增大，不是一步一步挪过去，而是「大步流星」、「连蹦带跳」走过去；
- 「逐渐缩小增量」「分组实施插入排序让数组变得逐渐接近有序」「最后执行一次标准的插入排序」（ 最后一轮就是「原汁原味」的插入排序。

「希尔排序」的实现比较多，我们这里只选取希尔排序的一种比较容易理解的实现。「希尔排序」也可以理解为「分组插入排序」。

希尔是计算机科学家的名字，所以希尔排序就得换一个名字来记。

希尔排序是 「**分组插入排序**」 或者 「**带间隔的插入排序**」。好处是：**让较小的元素一下子来到数组的前面**。

每一轮完成一次分组插入排序以后，数组就朝着接近有序的方向前进了一步。最后一轮一定是一次标准的插入排序



## 图示希尔排序

- 第 1 轮：把下标间隔为 5 的元素分成一组，一共 5 组，分别执行插入排序

![img](https://tva1.sinaimg.cn/large/008i3skNgy1gwyusfbmq0g30i8093k3y.gif)

此时数组比未排序的时候更接近有序了一点。

- 第 2 轮：把下标间隔为 2 的元素分成一组，一共 2 组，分别执行插入排序

![img](https://tva1.sinaimg.cn/large/008i3skNgy1gwyusit51eg30hw063wj7.gif)

此时数组比第 2 轮排序开始之前更接近有序了一点。

- 第 3 轮：把下标间隔为 1 的元素分成一组，其实就是标准的插入排序。

![img](https://tva1.sinaimg.cn/large/008i3skNgy1gwyush556qg30hy03lwfy.gif)



```Java
public class Solution {

    public int[] sortArray(int[] nums) {
        int len = nums.length;
        for (int detal = len / 2; detal > 0; detal /= 2) {
            // 以detal为间隔，就有detal组
            for (int start = 0; start < detal; start++) {
                insertionSortForDetal(nums, len, detal, start);
            }
        }
        return nums;
    }

    private void insertionSortForDetal(int[] nums, int len, int detal, int start) {
        // start为第几组的首元素，detal是步长
        for (int i = start + detal; i < len; i += detal) {
            int temp = nums[i];
            int j = i;
            for (; j - detal >= 0; j -= detal) {
                if (nums[j - detal] > temp) {
                    nums[j] = nums[j - detal];
                } else {
                    break;
                }
            }
            // 此时 nums[j - 1] <= temp
            // nums[j] 的值被赋值到了 nums[j + 1]
            nums[j] = temp;
        }
    }
}
```



## 希尔排序的时间复杂度

希尔排序的时间复杂度与选择的步长序列有关，最初的步长选择是2的次幂，时间复杂度是O(N^2)，后续算法改进过程中，步长选择的好能够有效提升时间复杂度，目前最好的效果在小数组中甚至比快排还快。

**总体来说，希尔排序比插入、冒泡、选择等基础排序算法要快，在小数组中甚至比快排还快，但是在大数组中，还是没有O(NlogN)级别的算法快。**

以前的空间是昂贵的，所以尽管归并提出的比希尔早，但人们还是在不断优化希尔排序，归并和快排等利用递归实现的排序算法，本质上是以空间换时间的思想。至于具体谁好谁坏，在算法的时间里，得看情况分析。



















