#include<iostream>
using namespace std; 

/*
������δ�����������ҵ���С����Ԫ�أ���ŵ��������е���ʼλ�á�

�ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�Ȼ��ŵ����������е�ĩβ��

�ظ��ڶ�����ֱ������Ԫ�ؾ�������ϡ�
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

