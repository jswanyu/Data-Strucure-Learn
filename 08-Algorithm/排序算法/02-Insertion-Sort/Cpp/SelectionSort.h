#pragma once
#include<iostream>
using namespace std; 

/*
ʱ�临�Ӷ�ΪO(n^2)���㷨��
1.����򵥣�����ʵ�֣���һЩ���龰����ѡ
2.��һЩ��������£��򵥵������㷨����Ч
3.�򵥵������㷨˼�����������ӵ������㷨
4.��Ϊ�ӹ��̣��Ľ������ӵ��㷨
*/

//ѡ������:
template<typename T>
void SelectionSort(T arr[], int n) //int --> T
{
	//int *arr��int arr[]������
	for (int i = 0; i < n; i++) {
		
		//Ѱ��[i,n)���������Сֵ
		int minIndex = i;  //��Сֵ������Ϊi
		for (int j = i + 1; j < n; j++)  //��i����һ������ʼ
			if (arr[j] < arr[minIndex])  //����ҵ�һ���ȵ�i����С�������Ͱ������ڵ�������Ϊ��ǰ�ִε���Сֵ
				minIndex = j; 
		swap(arr[i], arr[minIndex]);     //����Сֵ��������i������
	}
}

