#pragma once
#include<iostream>
using namespace std;


template<typename T>
void InsertionSort_Basic(T arr[], int n)
{
	for (int i = 1; i < n; i++) //外层的第i轮循环是将原数组的前i+1个数都排序完成
	{
		//寻找arr[i]合适的插入位置

		//写法1
		//for (int j = i; j > 0; j--)
		//{
		//	if (arr[j] < arr[j - 1])
		//		swap(arr[j], arr[j - 1]);
		//	else
		//		break;	
		//}

		//写法2
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			//内层的第j轮循环是判定第i+1个数，如果比前一个数小，就往前移动，直到放入合适的插入位置
			swap(arr[j], arr[j - 1]);
	}
}
//这种写法的缺点是内层循环比较时，需要不断交换符合条件的数据，浪费大量的时间，因此需要减少交换的次数



//改进的插入排序，只需记这个即可，后续对比排序算法的Insertionsort.h文件中也只有这个函数
template <typename T>
void InsertionSort_Advance(T* arr, int n)
{
	//[5,2,3,1] [2,3,5,1] e=3 2551  9 8 7 6  8 9 7 6  8 9 9 6 8 8 9 6 78 9 6
	for (int i = 1; i < n; i++)
	{
		T e = arr[i];  //复制一份外层循环当前轮次的元素
		int j;         //变量j保存元素e应该所在的位置，单独初始化是因为后面要用到

		//只要e前一个元素要比e大，那么就把前一个元素向后移，反之，退出for循环，找到了e合适的位置j
		//arr[j-1]比e小的话就不执行，进行下一轮外层循环，一旦比e大，后移，继续比e大，继续后移
		for (j = i; j > 0 && arr[j - 1] > e; j--)  
			arr[j] = arr[j - 1];         
		arr[j] = e;    
	}
}