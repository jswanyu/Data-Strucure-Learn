#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "BubbleSort.h"

using namespace std;


void test01()
{
	int n = 10000;
	int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);
	int* arr3 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //0.056s
	SortTestHelper::testSort("SelectionSort", SelectionSort, arr2, n);   //0.098s
	SortTestHelper::testSort("BubbleSort", BubbleSort, arr3, n);         //1.667s
	
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

	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //0.001s
	SortTestHelper::testSort("SelectionSort", SelectionSort, arr2, n);   //0.102s
	SortTestHelper::testSort("BubbleSort", BubbleSort, arr3, n);         //0.154s

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}



int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}