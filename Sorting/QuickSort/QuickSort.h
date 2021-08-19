#pragma once

#include <iostream>
#include <ctime>
#include "InsertionSort.h"

using namespace std;

// ��arr[l...r]���ֽ���partition����
// ����p, ʹ��arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
template<typename T>
int __partition(T *arr, int l, int r) {

    //�Ż�2����������ţ������arr[l...r]�ķ�Χ��, ѡ��һ����ֵ��Ϊ�궨��pivot
    //��Ȼ������ʱ�临�Ӷ���ȻΪO(n^2)���������ָ��ʷǳ�С���������ĸ��Ӷ�����O(nlogn)
    swap(arr[l],arr[rand()%(r-l+1)+l]);

    T v = arr[l];  //����������ߵ���ѡΪ�ȽϵĻ�׼

    // ����Ҫʹ��arr[ l+1 ... j ] < v ; arr[ j+1 ... i ) > v��һ��Ҫע���Ұ�ߵ� i �ǿ����䣬��Ϊi�ǵ�ǰ���ڱ�������Ԫ��
    // ��ʼֵj =l �ĺô����ʼ i = l+1 ʱ���������Ϊ[ l+1 ... l ] ���Ұ�����Ϊ[ l+1 ... l +1 )����Ϊ������
    // ���� j ��ָ��<v���ֵ����һ��λ��
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        //arr[i] > v ʱ���� i++ �Ϳ����ˣ��൱�ڲ��ù�
        if (arr[i] < v) {
            // j��ָ��<v�Ĳ��ֵ����һ��λ�ã�����Ӧ���ǽ���arr[i]��arr[j+1]�����j++������arr[i]�ͷŵ���<v�Ĳ���
            // �����i++��Ҳ��֤��ԭ����arr[j+1]��Ȼ��>v�Ĳ���
            // ����������Ժϲ�Ϊ�����ŵ�д����swap(arr[i], arr[++j]); //����ɽ�����Ҳ���+1
            swap(arr[i], arr[j + 1]);
            j++;
        }
    }

    swap(arr[l], arr[j]);
    return j;

}


// ��arr[l...r]���ֽ��п�������
template<typename T>
void __QuickSort(T *arr, int l, int r) {
//    if (l >= r)
//        return;
    //�Ż�һ������ݹ鵽��
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r);  //��������ֵ
    __QuickSort(arr, l, p - 1);      //ע��ֽ��
    __QuickSort(arr, p + 1, r);
}


template<typename T>
void QuickSort(T *arr, int n) {
    srand(time(NULL));   //�����
    __QuickSort(arr, 0, n - 1);
}



/**************************************  ˫·����   *********************************************************/
// ˫·���ŷ���p, ʹ��arr[l...p-1] <= arr[p] ; arr[p+1...r] >= arr[p]
// ���ѵ��ڱ궨ֵ�����������ȷֲ����������֣�������ɲ�ƽ������
template<typename T>
int __partition2(T *arr, int l, int r) {
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    // ʹ��arr[l+1...i) <= v; arr(j...r] >= v
    // �������������ֱ�ָ��<v�������һλ �� >v�����ǰһλ
    // ������ʼ������i��j��������ʼ����Ͷ��ǿյ�
    int i=l+1,j=r;
    while(1){
        // Խ�����⣺i�ǲ��ܱ�r��ģ���j�ǲ���С��l+1�ģ���Ϊl�Ǳ궨��
        // while�ж���arr[i]������<=v��arr[j]������>=v����Ϊ��������һ���ж�=�ɹ�������Ѵ�����ͬ���ݷ��õ�һ��������
        // ��Ȼ����ɲ�ƽ������⣬�����ǵ���Ҳ�ܺ���⣬iָ�����>=v������jָ�����<=v������Ȼ�󽻻����ǣ���v��ȵ�������������һ�ߣ�
        // ���i++��j--������������������������������Ȳ�����v�����к���Ԫ�ص��ж�
        while(i<=r && arr[i]<v) i++;
        while(j>=l+1 && arr[j]>v) j--;
        if(i>j) break;
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    // ����������iָ���ǰ���󿴵�һ��>=v��λ�ã�jָ��Ӻ���ǰ�������һ��<=v��λ�ã�
    // ���ڱ궨������<=v��һ�ˣ����Խ���arr[l]��arr[j]�����Ƕ���<=v�����ֵ
    swap(arr[l],arr[j]);

    return j;
}


// ��arr[l...r]���ֽ��п�������
template<typename T>
void __QuickSort2(T *arr, int l, int r) {
    //    if (l >= r)
    //        return;
    //�Ż�һ������ݹ鵽��
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition2(arr, l, r);  //��������ֵ
    __QuickSort2(arr, l, p - 1);
    __QuickSort2(arr, p + 1, r);
}


template<typename T>
void QuickSort2(T *arr, int n) {
    srand(time(NULL));
    __QuickSort2(arr, 0, n - 1);
}


/**************************************  ��·����   *********************************************************/

//��arr[l...r]��Ϊ<v;==v;>v ������
//֮��ݹ��<v;>v�����ֽ�����·����
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
    if(r-l<=15){
        InsertionSort(arr,l,r);
        return;
    }

    //partition
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    int lt = l;    //arr[l+1...lt]<v, ltָ��<v�����һλ, lt(less than)
    int gt = r+1;  //arr[gt...r]>v    gtָ��>v�ĵ�һλ, gt(greater than)
    int i = l+1;   //arr[l+1...i)==v  iָ��������Ԫ��

    while(i<gt){
        if(arr[i]<v){
            swap(arr[i],arr[lt+1]);
            lt++;
            i++;
        }
        else if(arr[i]>v){
            swap(arr[i],arr[gt-1]);
            gt--; //���ﲻ��Ҫ����i++��iָ�򽻻�������arr[gt-1]������Ȼ�Ǹ�δ�жϵ�ֵ
        }
        else{//arr[i]==v
            i++;
        }
    }
    swap(arr[l],arr[lt]);  //arr[l]�ǵ���v�ģ�����arr[lt]�������ݹ�lt֮ǰ�Ĳ��֣���lt-1

    // c++�����㷵��һ��������������ֱ�ӵݹ飬����дר�ŵ�partition����
    __quickSort3Ways(arr,l,lt-1);  //�������׳����ǵݹ�lt֮ǰ�Ĳ��֣���lt-1
    __quickSort3Ways(arr,gt,r);
}


template<typename T>
void quickSort3Ways(T arr[],int n){
    srand(time(NULL));
    __quickSort3Ways(arr,0,n-1);
}