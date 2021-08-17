#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

// 测试1 一般性测试
// 比较InsertionSort和MergeSort两种排序算法的性能效率，整体而言, MergeSort的性能最优
void test01()
{
	int n = 100000;
	cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;

	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	
	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //4.949s
	SortTestHelper::testSort("MergeSort", MergeSort, arr2, n);           //0.012s

	delete[] arr1;
	delete[] arr2;

	cout<<endl;
}

// 测试2 测试近乎有序的数组
// 对于近乎有序的数组, 数组越有序, InsertionSort的时间性能越趋近于O(n)
// 所以可以尝试, 当swapTimes比较大时, MergeSort更快
// 但是当swapTimes小到一定程度, InsertionSort变得比MergeSort快
void test02()
{
	int n =500000;
	int swapTimes = 10;
	cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;

	int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);  //近乎有序的数组
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //0.002s
	SortTestHelper::testSort("MergeSort", MergeSort, arr2, n);           //0.046s 优化后：0.002s

	delete[] arr1;
	delete[] arr2;
}



int main() {
	test01();
	test02();
	return 0;
}