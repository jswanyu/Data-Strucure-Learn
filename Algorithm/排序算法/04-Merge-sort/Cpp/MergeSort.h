#pragma once
#include<iostream>
using namespace std;

/*�鲢����
���õݹ��˼���������
*/


// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
template<typename T>
void __Merge(T arr[], int l, int mid, int r)
{
    // vs��֧�ֶ�̬�������飬������ʹ��T aux[r-l+1]�ķ�ʽ������aux�Ŀռ�
    // Ҫʹ��new�ķ�ʽ����aux�ռ䣬��__merge���������, delete������Ŀռ�
    // T *aux = new T[r - l + 1];

    T aux[r-l+1];                 //���ٸ�������ռ�
	
	for (int i = l; i <= r; i++)  //��������
		aux[i - l] = arr[i];      //��ֵ��ʱ����һ��l��ƫ����

	int i = l, j = mid + 1;       //��������ָ��ֱ�ָ�����Ұ�������λ��
	for (int k = l; k <= r; k++)
	{
		//�����i��j��++������Ҫ���ж������ĺϷ��ԣ���֤��Խ��
		if (i > mid)                         //�����ߵ������Ѿ�����mid��˵��������Ѿ���������
		{
			arr[k] = aux[j - l];         //���Ұ���ʣ�µ����ַ���arr
			j++;
		}
		else if (j > r)                    //�Ұ���Խ��ͬ��
		{
			arr[k] = aux[i - l];
			i++;
		}
		//���ж������鲿��
		else if (aux[i - l] < aux[j - l])   //����������һ����С���Ұ�����һ����
		{
			arr[k] = aux[i - l];                //��������ĵ�һλ�ͷ�������ĵ�һ����
			i++;                                      //����ͬ��
		}
		else
		{ 
			arr[k] = aux[j - l];                //������������ĵ�һλ�ͷ��Ұ����ĵ�һ����
			j++;                                      //����ͬ��
		}
	}
	//delete[] aux;
}


//�ݹ�ʹ�ù鲢���򣬶�arr[l...r]�ķ�Χ��������l�ǵ�һ��Ԫ�ص�λ�ã�r�����һ��Ԫ�ص�λ�ã����߶��Ǳ�����
//������������£��ڵݹ���ó���Ϊn������ʱ��l����������±�λ��0��r����������±�λ��n-1

//��������ﶨ��Ϊ����ҿ���[l...r)��Χ����ô�����r���Ǵ������������һ��Ԫ�ص���һ��λ��
template<typename T>
void __MergeSort(T* arr, int l, int r)
{
	//���l>=r����ô��Ȼ������Ԫ��ֻ��0��1������ôֱ�ӷ���ȥ����
    //	if (l >= r)
    //		return;

    // �Ż�1: ����С��ģ����, ʹ�ò������򣬱���ݹ鵽��
    if(r-l <= 15)
    {
        InsertionSort(arr, l, r);  //��Ҫ��֮ǰ[0,n]����Ĳ��������дΪ[l,r]��
        return;
    }


	int mid = (l + r) / 2;        //�������ַǳ���ʱ����������ݵ��������
	__MergeSort(arr,l,mid);     //������ݹ�����
	__MergeSort(arr,mid+1,r);   //�Ұ����ݹ����� 
	//__Merge(arr,l,mid,r);         //����������

	// �Ż�2: ����arr[mid] <= arr[mid+1]�����,������merge
	// ��Ϊ�鲢���̱�֤��l~mid������ģ�mid+1~rҲ������ģ�arr[mid] <= arr[mid+1]����������
	// ���ڽ������������ǳ���Ч,���Ƕ���һ�����,��һ����������ʧ
	if (arr[mid] > arr[mid + 1])
	    __Merge(arr, l, mid, r);
}


template<typename T>
void MergeSort(T arr[], int n) {
	__MergeSort(arr, 0, n - 1);
}
