#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "SelectionSort.h"

using namespace std;


void test01()
{
	int n = 10000;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);
	
	SortTestHelper::testSort("InsertionSort_Basic", InsertionSort_Basic, arr1, n);   //1.714s
	SortTestHelper::testSort("InsertionSort_Basic", InsertionSort_Advance, arr2, n); //0.047s
	SortTestHelper::testSort("SelectionSort", SelectionSort, arr3, n);   //0.094s
	
	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}

void test02()
{
	int n = 10000;
	int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,100);  //近乎有序的数组
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("InsertionSort", InsertionSort_Basic, arr1, n);   //0.046s
	SortTestHelper::testSort("InsertionSort", InsertionSort_Advance, arr2, n);   //0.001s
	SortTestHelper::testSort("SelectionSort", SelectionSort, arr3, n);   //0.098s

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;

}
//可以发现对于近乎有序数组，插入排序非常快，这具有非常重要的意义，因为日常有时候的数据就是近乎有序的


int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}