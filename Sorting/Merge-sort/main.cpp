#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

// 比较InsertionSort和MergeSort两种排序算法的性能效率，整体而言, MergeSort的性能最优
void test01()
{
	int n = 50000;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);

	
	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //1.304s
	SortTestHelper::testSort("MergeSort", MergeSort, arr2, n);           //0.02s
	SortTestHelper::testSort("MergeSort2", MergeSort2, arr3, n);       //0.007s

	
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

}

// 测试2 测试近乎有序的数组
// 对于近乎有序的数组, 数组越有序, InsertionSort的时间性能越趋近于O(n)
// 所以可以尝试, 当swapTimes比较大时, MergeSort更快
// 但是当swapTimes小到一定程度, InsertionSort变得比MergeSort快

void test02()
{
	int n =50000;
	int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,500);  //近乎有序的数组
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //0.021s
	SortTestHelper::testSort("MergeSort", MergeSort, arr2, n);           //0.021s
	SortTestHelper::testSort("MergeSort2", MergeSort2, arr3, n);       //0.003s

	
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}



int main() {
	test01();
	test02();
	system("pause");
	return 0;
}