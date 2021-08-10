#pragma once
#include<iostream>
#include<ctime>
#include<cassert>

using namespace std;

namespace SortTestHelper {

	/*
	rand() % a         表示生成[0,a-1]的一个随机整数，这是固定语法
	rand() % (a+1)     表示生成[0,a]的一个随机整数
	rand() % (a+1)+a   表示生成[a,2a]的一个随机整数
	rand() % (b-a+1)+a 表示生成[a,b]的一个随机整数
	*/
	//生成有n个元素的随机数组，每个元素的随机范围是[rangeL,rangeR]

	int* generateRandomArray(int n, int rangeL, int rangeR)
	{
		assert(rangeL <= rangeR);  //assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行

		int* arr = new int[n];
		srand(time(NULL));  //将当前时间作为种子产生随机数
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;  //rangeL + [0,rangeR-rangeL]
		}
		return arr;
	}


	//打印数组
	template<typename T>
	void printArray(T arr[], int n)
	{
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << endl;
		return;
	}



	//判断排序是否正确
	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}



	//计算排序运行时间
	template<typename T>
	void testSort(string sortName, void (*sort)(T[], int n), T arr[], int n)   //将函数传入参数
	{
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));  //确保排序成功，否则中断

		cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		//endTime - startTime返回的是运行了几个时钟周期
		//CLOCKS_PER_SEC代表每秒钟有几个时钟周期，相除得到运行了多少秒

		return;
	}
	

	//返回复制的整型数组
	int* copyIntArray(int a[], int n)
	{
		int* arr = new int[n];
		copy(a, a + n, arr);
		return arr;
	}


}