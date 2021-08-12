# 归并排序

## 一、概念及其介绍

归并排序（Merge sort）是建立在归并操作上的一种有效、稳定的排序算法，该算法是采用分治法(Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。

作为一种典型的分而治之思想的算法应用，归并排序的实现由两种方法：

- 自上而下的递归（所有递归的方法都可以用迭代重写，所以就有了第 2 种方法）；
- 自下而上的迭代；



### 算法步骤

1. 申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列；
2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置；
3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置；
4. 重复步骤 3 直到某一指针达到序列尾；
5. 将另一序列剩下的所有元素直接复制到合并序列尾。



## 二、算法性能

|   算法   | 最好时间  | 最坏时间 | 平均时间 | 额外空间 | 稳定性 |
| :------: | :-------: | :------: | :------: | :------: | :----: |
| 归并排序 | O(nlogn） | O(nlogn) | O(nlogn) |   O(n)   |  稳定  |

归并排序的性能不受输入数据的影响，始终都是 O(nlogn) 的时间复杂度。代价是需要额外的内存空间。

归并排序适用于数据量大，并且对稳定性有要求的场景

## 三、过程图示

![插入排序示意图](https://github.com/wanyu416/Data-Strucure/blob/main/src/mergeSort.gif)



## 四、实例代码

利用递归进行自顶向下的归并排序

```c++
// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __Merge(T arr[], int l, int mid, int r)
{
	//vs不支持动态长度数组，即不能使用T aux[r-l+1]的方式来申请aux的空间
	T *aux = new T[r - l + 1];    //开辟复制数组空间
	
	for (int i = l; i <= r; i++)  //复制数组
		aux[i - l] = arr[i];      //赋值的时候有一个l的偏移量

	int i = l, j = mid + 1;       //定义两个指针分别指向左右半区的首位置
	for (int k = l; k <= r; k++)
	{
		//后面的i和j会++，所以要先判断索引的合法性，保证不越界
		if (i > mid)                         //如果左边的索引已经大于mid，说明左半区已经都排序完
		{
			arr[k] = aux[j - l];             //把右半区剩下的数字放入arr
			j++;
		}
		else if (j > r)                      //右半区越界同理
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
	delete[] aux;
}


//递归使用归并排序，对arr[l...r]的范围进行排序，l是第一个元素的位置，r是最后一个元素的位置，两边都是闭区间
//所以这种情况下，在递归调用长度为n的数组时，l就是数组的下标位置0，r就是数组的下标位置n-1
//如果在这里定义为左闭右开的[l...r)范围，那么这里的r就是传入数组里最后一个元素的下一个位置
template<typename T>
void __MergeSort(T* arr, int l, int r)
{
	//如果l>=r，那么显然待排序元素只有0或1个，那么直接返回去即可
	if (l >= r)
		return;

	int mid = (l + r) / 2;        //两个数字非常大时，会造成数据的溢出问题
	__MergeSort(arr,l,mid);       //左半区递归排序
	__MergeSort(arr,mid+1,r);     //右半区递归排序 
	__Merge(arr,l,mid,r);         //核心排序函数
}


template<typename T>
void MergeSort(T* arr, int n)
{
	__MergeSort(arr, 0 ,n-1);   //表明该函数是私有函数，不希望被用户调用
}
```



文件结构：

MergeSort.h  冒泡排序算法

InsertionSort.h  插入排序算法

SortTestHelper.h  测试函数

main.cpp  主函数



## 五、改进

### 改进一：对于左半区和右半区整体大小已经确定的情况可以不用再进行递归

对于arr[mid] <= arr[mid+1]的情况,不进行merge ，因为归并过程保证了l~mid是有序的，mid+1~r也是有序的，arr[mid] <= arr[mid+1]，则不用排序，这对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失

```c++
//归并排序的优化

template<typename T>
void __MergeSort2(T arr[], int l, int r)
{
	if (l >= r)
		return;

	int mid = (l + r) / 2;
	__MergeSort2(arr, l, mid);
	__MergeSort2(arr, mid+1, r);

	// 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
    // 因为归并过程保证了l~mid是有序的，mid+1~r也是有序的，arr[mid] <= arr[mid+1]，则不用排序
    // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
	if (arr[mid] > arr[mid + 1])
		__Merge(arr, l, mid, r);
}
```

### 改进二：对于小规模数组, 使用插入排序，避免递归到底

```c++
template<typename T>
void __MergeSort2(T arr[], int l, int r)
{
	// 优化2: 对于小规模数组, 使用插入排序，避免递归到底
	if(r-l <= 15)
	{
		InsertionSort(arr, l, r);  //需要将之前[0,n]数组的插入排序改写为[l,r]的
		return;
	}

	int mid = (l + r) / 2;
	__MergeSort2(arr, l, mid);
	__MergeSort2(arr, mid+1, r);

	// 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
   // 因为归并过程保证了l~mid是有序的，mid+1~r也是有序的，arr[mid] <= arr[mid+1]，则不用排序
   // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
	if (arr[mid] > arr[mid + 1])
		__Merge(arr, l, mid, r);
}
```

