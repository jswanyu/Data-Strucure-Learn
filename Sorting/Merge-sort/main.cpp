#include<iostream>
#include<string>

#include "InsertionSort.h"
#include "SortTestHelper.h"
#include "MergeSort.h"

using namespace std;

// ����1 һ���Բ���
// �Ƚ�InsertionSort��MergeSort���������㷨������Ч�ʣ��������, MergeSort����������
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

// ����2 ���Խ������������
// ���ڽ������������, ����Խ����, InsertionSort��ʱ������Խ������O(n)
// ���Կ��Գ���, ��swapTimes�Ƚϴ�ʱ, MergeSort����
// ���ǵ�swapTimesС��һ���̶�, InsertionSort��ñ�MergeSort��
void test02()
{
	int n =500000;
	int swapTimes = 10;
	cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;

	int* arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);  //�������������
	int* arr2 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("InsertionSort", InsertionSort, arr1, n);   //0.002s
	SortTestHelper::testSort("MergeSort", MergeSort, arr2, n);           //0.046s �Ż���0.002s

	delete[] arr1;
	delete[] arr2;
}



int main() {
	test01();
	test02();
	return 0;
}