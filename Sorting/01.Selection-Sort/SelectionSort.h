#include<iostream>
using namespace std; 


template<typename T>
void SelectionSort(T arr[], int n) //int --> T
{
	//int *arr和int arr[]都可以
	for (int i = 0; i < n; i++) {
		
		//寻找[i,n)区间里的最小值
		int minIndex = i;  //最小值的索引为i
		for (int j = i + 1; j < n; j++)  //从i的下一个数开始
			if (arr[j] < arr[minIndex])  //如果找到一个比第i个数小的数，就把他所在的索引记为当前轮次的最小值
				minIndex = j; 
		swap(arr[i], arr[minIndex]);     //将最小值交换到第i个数处
	}
}

