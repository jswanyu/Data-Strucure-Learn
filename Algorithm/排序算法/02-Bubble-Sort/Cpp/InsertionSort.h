#pragma once
#include<iostream>
using namespace std;


//��������
template <typename T>
void InsertionSort(T* arr, int n)
{
	for(int i=1;i<n;i++)
	{
		//���ڲ�ѭ�����и�д��Ѱ��Ԫ��arr[i]���ʵĲ���λ��
		T e = arr[i];  //����һ�����ѭ����ǰ�ִε�Ԫ��
		int j;  //����j����Ԫ��eӦ�����ڵ�λ�ã�������ʼ������Ϊ����Ҫ�õ�
		for(j=i;j>0 && arr[j-1]>e; j--)  //ֻҪeǰһ��Ԫ��Ҫ��e����ô�Ͱ�ǰһ��Ԫ������ƣ�
			                             //�������������ô˵���ҵ��������ڵ�λ��
		{
			arr[j] = arr[j - 1]; //ǰһ��λ�õ�Ԫ�������һ��
		}
		arr[j] = e;
	}
}