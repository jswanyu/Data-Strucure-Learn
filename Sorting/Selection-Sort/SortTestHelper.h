#pragma once
#include<iostream>
#include<ctime>
#include<cassert>

using namespace std;

namespace SortTestHelper {

	/*
	rand() % a         ��ʾ����[0,a-1]��һ��������������ǹ̶��﷨
	rand() % (a+1)     ��ʾ����[0,a]��һ���������
	rand() % (a+1)+a   ��ʾ����[a,2a]��һ���������
	rand() % (b-a+1)+a ��ʾ����[a,b]��һ���������
	*/
	//������n��Ԫ�ص�������飬ÿ��Ԫ�ص������Χ��[rangeL,rangeR]

	int* generateRandomArray(int n, int rangeL, int rangeR)
	{
		assert(rangeL <= rangeR);  //assert���ԭ�Ͷ�����<assert.h>�У�����������������������ش�������ֹ����ִ��

		int* arr = new int[n];
		srand(time(NULL));  //����ǰʱ����Ϊ���Ӳ��������
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;  //rangeL + [0,rangeR-rangeL]
		}
		return arr;
	}


	//��ӡ����
	template<typename T>
	void printArray(T arr[], int n)
	{
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
		return;
	}



	//�ж������Ƿ���ȷ
	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}



	//������������ʱ��
	template<typename T>
	void testSort(string sortName, void (*sort)(T[], int n), T arr[], int n)   //�������������
	{
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));  //ȷ������ɹ��������ж�

		cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		//endTime - startTime���ص��������˼���ʱ������
		//CLOCKS_PER_SEC����ÿ�����м���ʱ�����ڣ�����õ������˶�����

		return;
	}
	

	//���ظ��Ƶ���������
	int* copyIntArray(int a[], int n)
	{
		int* arr = new int[n];
		copy(a, a + n, arr);
		return arr;
	}


}