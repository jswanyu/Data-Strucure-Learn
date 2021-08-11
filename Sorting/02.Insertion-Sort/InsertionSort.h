#pragma once
#include<iostream>
using namespace std;


template<typename T>
void InsertionSort_Basic(T arr[], int n)
{
	for (int i = 1; i < n; i++) //���ĵ�i��ѭ���ǽ�ԭ�����ǰi+1�������������
	{
		//Ѱ��arr[i]���ʵĲ���λ��

		//д��1
		//for (int j = i; j > 0; j--)
		//{
		//	if (arr[j] < arr[j - 1])
		//		swap(arr[j], arr[j - 1]);
		//	else
		//		break;	
		//}

		//д��2
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
			//�ڲ�ĵ�j��ѭ�����ж���i+1�����������ǰһ����С������ǰ�ƶ���ֱ��������ʵĲ���λ��
			swap(arr[j], arr[j - 1]);
	}
}
//����д����ȱ�����ڲ�ѭ���Ƚ�ʱ����Ҫ���Ͻ����������������ݣ��˷Ѵ�����ʱ�䣬�����Ҫ���ٽ����Ĵ���



//�Ľ��Ĳ�������ֻ���������ɣ������Ա������㷨��Insertionsort.h�ļ���Ҳֻ���������
template <typename T>
void InsertionSort_Advance(T* arr, int n)
{
	//[5,2,3,1] [2,3,5,1] e=3 2551  9 8 7 6  8 9 7 6  8 9 9 6 8 8 9 6 78 9 6
	for (int i = 1; i < n; i++)
	{
		T e = arr[i];  //����һ�����ѭ����ǰ�ִε�Ԫ��
		int j;         //����j����Ԫ��eӦ�����ڵ�λ�ã�������ʼ������Ϊ����Ҫ�õ�

		//ֻҪeǰһ��Ԫ��Ҫ��e����ô�Ͱ�ǰһ��Ԫ������ƣ���֮���˳�forѭ�����ҵ���e���ʵ�λ��j
		//arr[j-1]��eС�Ļ��Ͳ�ִ�У�������һ�����ѭ����һ����e�󣬺��ƣ�������e�󣬼�������
		for (j = i; j > 0 && arr[j - 1] > e; j--)  
			arr[j] = arr[j - 1];         
		arr[j] = e;    
	}
}