#include<iostream>
using namespace std; 

/*
首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。

再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。

重复第二步，直到所有元素均排序完毕。
*/

//选择排序:
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

