#pragma once
#include<iostream>
using namespace std;

template<typename T>
void BubbleSort(T *arr,int n)
{
	for (int i = 0; i < n - 1; i++) //����n������ÿһ�ֱȽ�ð��һ�������������һ��������ð������Ҫ�Ƚ�n-1��
		for (int j = 0; j < n - 1 - i; j++) //n�����У����ڵ�Ԫ�ؾ���n-1��,��0��Ҫ�Ƚ�n-1��,��i��Ҫ�Ƚ�n-1-i��
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}