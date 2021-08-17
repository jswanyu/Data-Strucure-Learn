#pragma once
#include<iostream>
using namespace std;

//插入排序
template <typename T>
void InsertionSort(T* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		//对内层循环进行改写，寻找元素arr[i]合适的插入位置
		T e = arr[i];  //复制一份外层循环当前轮次的元素
		int j;  //变量j保存元素e应该所在的位置，单独初始化是因为后面要用到
		for (j = i; j > 0 && arr[j - 1] > e; j--)  //只要e前一个元素要比e大，那么就把前一个元素向后移，
										 //如果不比它大，那么说明找到了它该在的位置
		{
			arr[j] = arr[j - 1]; //前一个位置的元素向后移一下
		}
		arr[j] = e;
	}
}


// 对arr[l...r]范围的数组进行插入排序，要注意外层循环里是<=r
template <typename T>
void InsertionSort(T* arr, int l, int r)
{
	for (int i = l + 1;  i <= r; i++)
	{
		T e = arr[i];
		int j;
		for (j = i; j > l && arr[j - 1] > e; j--)
			arr[j] = arr[j - 1];
		arr[j] = e;
	}
}