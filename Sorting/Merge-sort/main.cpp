#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

// �Ƚ�InsertionSort��MergeSort���������㷨������Ч�ʣ��������, MergeSort����������
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

// ����2 ���Խ������������
// ���ڽ������������, ����Խ����, InsertionSort��ʱ������Խ������O(n)
// ���Կ��Գ���, ��swapTimes�Ƚϴ�ʱ, MergeSort����
// ���ǵ�swapTimesС��һ���̶�, InsertionSort��ñ�MergeSort��

void test02()
{
	int n =50000;
	int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,500);  //�������������
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