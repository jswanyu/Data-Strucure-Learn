#pragma once
#include<iostream>
using namespace std; 

/*
时间复杂度为O(n^2)的算法：
1.编码简单，易于实现，是一些简单情景的首选
2.在一些特殊情况下，简单的排序算法更有效
3.简单的排序算法思想衍生出复杂的排序算法
4.作为子过程，改进更复杂的算法
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

