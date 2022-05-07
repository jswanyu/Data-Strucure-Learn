#pragma once
#include<iostream>
using namespace std;

template<typename T>
void BubbleSort(T *arr,int n)
{
	for (int i = 0; i < n - 1; i++) //对于n个数，每一轮比较冒出一个最大的数，最后一个数不用冒，所以要比较n-1轮
		for (int j = 0; j < n - 1 - i; j++) //n个数中，相邻的元素就有n-1组,第0轮要比较n-1次,第i轮要比较n-1-i次
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}