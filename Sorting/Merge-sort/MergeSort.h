#pragma once
#include<iostream>
using namespace std;

/*归并排序
利用递归的思想进行排序
*/


// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __Merge(T arr[], int l, int mid, int r)
{
    // vs不支持动态长度数组，即不能使用T aux[r-l+1]的方式来申请aux的空间
    // 要使用new的方式申请aux空间，在__merge函数的最后, delete掉申请的空间
    // T *aux = new T[r - l + 1];

    T aux[r-l+1];                 //开辟复制数组空间
	
	for (int i = l; i <= r; i++)  //复制数组
		aux[i - l] = arr[i];      //赋值的时候有一个l的偏移量

	int i = l, j = mid + 1;       //定义两个指针分别指向左右半区的首位置
	for (int k = l; k <= r; k++)
	{
		//后面的i和j会++，所以要先判断索引的合法性，保证不越界
		if (i > mid)                         //如果左边的索引已经大于mid，说明左半区已经都排序完
		{
			arr[k] = aux[j - l];         //把右半区剩下的数字放入arr
			j++;
		}
		else if (j > r)                    //右半区越界同理
		{
			arr[k] = aux[i - l];
			i++;
		}
		//再判断子数组部分
		else if (aux[i - l] < aux[j - l])   //如果左半区第一个数小于右半区第一个数
		{
			arr[k] = aux[i - l];                //整个数组的第一位就放左半区的第一个数
			i++;                                      //后续同理
		}
		else
		{ 
			arr[k] = aux[j - l];                //否则整个数组的第一位就放右半区的第一个数
			j++;                                      //后续同理
		}
	}
	//delete[] aux;
}


//递归使用归并排序，对arr[l...r]的范围进行排序，l是第一个元素的位置，r是最后一个元素的位置，两边都是闭区间
//所以这种情况下，在递归调用长度为n的数组时，l就是数组的下标位置0，r就是数组的下标位置n-1

//如果在这里定义为左闭右开的[l...r)范围，那么这里的r就是传入数组里最后一个元素的下一个位置
template<typename T>
void __MergeSort(T* arr, int l, int r)
{
	//如果l>=r，那么显然待排序元素只有0或1个，那么直接返回去即可
    //	if (l >= r)
    //		return;

    // 优化1: 对于小规模数组, 使用插入排序，避免递归到底
    if(r-l <= 15)
    {
        InsertionSort(arr, l, r);  //需要将之前[0,n]数组的插入排序改写为[l,r]的
        return;
    }


	int mid = (l + r) / 2;        //两个数字非常大时，会造成数据的溢出问题
	__MergeSort(arr,l,mid);     //左半区递归排序
	__MergeSort(arr,mid+1,r);   //右半区递归排序 
	//__Merge(arr,l,mid,r);         //核心排序函数

	// 优化2: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
	// 因为归并过程保证了l~mid是有序的，mid+1~r也是有序的，arr[mid] <= arr[mid+1]，则不用排序
	// 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
	if (arr[mid] > arr[mid + 1])
	    __Merge(arr, l, mid, r);
}


template<typename T>
void MergeSort(T arr[], int n) {
	__MergeSort(arr, 0, n - 1);
}
