#pragma once
#include<iostream>
using namespace std;

//��������
template <typename T>
void InsertionSort(T* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		//���ڲ�ѭ�����и�д��Ѱ��Ԫ��arr[i]���ʵĲ���λ��
		T e = arr[i];  //����һ�����ѭ����ǰ�ִε�Ԫ��
		int j;  //����j����Ԫ��eӦ�����ڵ�λ�ã�������ʼ������Ϊ����Ҫ�õ�
		for (j = i; j > 0 && arr[j - 1] > e; j--)  //ֻҪeǰһ��Ԫ��Ҫ��e����ô�Ͱ�ǰһ��Ԫ������ƣ�
										 //�������������ô˵���ҵ��������ڵ�λ��
		{
			arr[j] = arr[j - 1]; //ǰһ��λ�õ�Ԫ�������һ��
		}
		arr[j] = e;
	}
}


// ��arr[l...r]��Χ��������в�������Ҫע�����ѭ������<=r
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