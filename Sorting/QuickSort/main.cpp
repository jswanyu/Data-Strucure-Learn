#include<iostream>
#include<string>

#include "QuickSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

// 测试1 一般性测试
// 几种优化方法对于一般性测试没太大影响
void test01()
{
    //如果造成堆栈溢出问题，修改CMakeLists文件
    int n = 1000000;
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("MergeSort", MergeSort, arr1, n);             //0.142s
    SortTestHelper::testSort("QuickSort", QuickSort, arr2, n);             //0.163s
    SortTestHelper::testSort("QuickSort2", QuickSort2, arr3, n);           //0.103s
    SortTestHelper::testSort("quickSort3Ways", quickSort3Ways, arr4, n);   //0.146s

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<endl;
}


// 测试2 测试近乎有序的数组
// 未优化的快排对近乎有序的数组排序非常慢，因为partition操作的基数选择了最左侧的数，其在近乎有序的数组中递归时
// 分界点大概率都是最左侧，递归树的高度就成了n，导致其变成近乎O(n^2)的复杂度，优化方法为使用随机化快排
// 优化后虽然还是没有归并快（归并使用了优化，近乎有序的数组不用归并过程），但在可以接受的范围内
void test02()
{
    int n =1000000;
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;

    int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);  //近乎有序的数组
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("MergeSort", MergeSort, arr1, n);             //0.005s
    SortTestHelper::testSort("QuickSort", QuickSort, arr2, n);             //4.093s 改为随机化之后0.115s
    SortTestHelper::testSort("QuickSort2", QuickSort2, arr3, n);           //0.092s
    SortTestHelper::testSort("quickSort3Ways", quickSort3Ways, arr4, n);   //0.268s

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<endl;
}


// 测试3 测试存在包含大量相同元素的数组
// 对于含有大量相同元素的数组, 快速排序算法再次退化成了O(n^2)级别的算法，因为=v的数据太多，不管是放在>v的区域还是<v的区域
// 都会造成数组分布极度不平衡，所以时间复杂度退化成了O(n^2)，解决的方法是使用双路快排
// 三路快速排序是双路快速排序的进一步改进版本,把排序的数据分为三部分，分别为小于 v，等于 v，大于 v，v 为标定值，这样三部分的数据中，
// 等于v的数据在下次递归中不再需要排序
void test03(){
    int n =1000000;
    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,10);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", MergeSort, arr1, n);            //0.099s
    SortTestHelper::testSort("Quick Sort", QuickSort, arr2, n);            //80.417s
    SortTestHelper::testSort("Quick Sort2", QuickSort2, arr3, n);          //0.066s
    SortTestHelper::testSort("quickSort3Ways", quickSort3Ways, arr4, n);   //0.025s

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
}



int main() {
    test01();
    test02();
    test03();
    return 0;
}