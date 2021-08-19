#pragma once

#include <iostream>
#include <ctime>
#include "InsertionSort.h"

using namespace std;

// 对arr[l...r]部分进行partition操作
// 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
template<typename T>
int __partition(T *arr, int l, int r) {

    //优化2：随机化快排：随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
    //虽然最坏情况的时间复杂度仍然为O(n^2)，但是这种概率非常小，而期望的复杂度则是O(nlogn)
    swap(arr[l],arr[rand()%(r-l+1)+l]);

    T v = arr[l];  //将数组最左边的数选为比较的基准

    // 下面要使得arr[ l+1 ... j ] < v ; arr[ j+1 ... i ) > v，一定要注意右半边的 i 是开区间，因为i是当前正在被检索的元素
    // 初始值j =l 的好处是最开始 i = l+1 时，左半区间为[ l+1 ... l ] ，右半区间为[ l+1 ... l +1 )，均为空区间
    // 索引 j 是指向<v部分的最后一个位置
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        //arr[i] > v 时，让 i++ 就可以了，相当于不用管
        if (arr[i] < v) {
            // j是指向<v的部分的最后一个位置，所以应该是交换arr[i]和arr[j+1]，随后j++，这样arr[i]就放到了<v的部分
            // 再随后i++，也保证了原来的arr[j+1]仍然在>v的部分
            // 下面两句可以合并为更优雅的写法：swap(arr[i], arr[++j]); //既完成交换，也完成+1
            swap(arr[i], arr[j + 1]);
            j++;
        }
    }

    swap(arr[l], arr[j]);
    return j;

}


// 对arr[l...r]部分进行快速排序
template<typename T>
void __QuickSort(T *arr, int l, int r) {
//    if (l >= r)
//        return;
    //优化一，避免递归到底
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r);  //返回索引值
    __QuickSort(arr, l, p - 1);      //注意分界点
    __QuickSort(arr, p + 1, r);
}


template<typename T>
void QuickSort(T *arr, int n) {
    srand(time(NULL));   //随机化
    __QuickSort(arr, 0, n - 1);
}



/**************************************  双路快排   *********************************************************/
// 双路快排返回p, 使得arr[l...p-1] <= arr[p] ; arr[p+1...r] >= arr[p]
// 即把等于标定值的数尽量均匀分布在两个部分，不会造成不平衡的情况
template<typename T>
int __partition2(T *arr, int l, int r) {
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    // 使得arr[l+1...i) <= v; arr(j...r] >= v
    // 定义两个索引分别指向：<v区域的下一位 和 >v区域的前一位
    // 这样初始化定义i，j，两个初始区间就都是空的
    int i=l+1,j=r;
    while(1){
        // 越界问题：i是不能比r大的，而j是不能小于l+1的，因为l是标定点
        // while判定中arr[i]不能是<=v，arr[j]不能是>=v，因为其中任意一个判定=成功，都会把大量相同数据放置到一个半区，
        // 仍然会造成不平衡的问题，而不是等于也很好理解，i指向这个>=v的数，j指向这个<=v的数，然后交换他们，与v相等的数交换到了另一边，
        // 随后i++，j--，跳过这个交换过来的数，不管他等不等于v，进行后面元素的判定
        while(i<=r && arr[i]<v) i++;
        while(j>=l+1 && arr[j]>v) j--;
        if(i>j) break;
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
    // 遍历结束后，i指向从前往后看第一个>=v的位置，j指向从后往前看，最后一个<=v的位置，
    // 现在标定点是在<=v这一端，所以交换arr[l]和arr[j]，它们都是<=v区域的值
    swap(arr[l],arr[j]);

    return j;
}


// 对arr[l...r]部分进行快速排序
template<typename T>
void __QuickSort2(T *arr, int l, int r) {
    //    if (l >= r)
    //        return;
    //优化一，避免递归到底
    if (r - l <= 15) {
        InsertionSort(arr, l, r);
        return;
    }

    int p = __partition2(arr, l, r);  //返回索引值
    __QuickSort2(arr, l, p - 1);
    __QuickSort2(arr, p + 1, r);
}


template<typename T>
void QuickSort2(T *arr, int n) {
    srand(time(NULL));
    __QuickSort2(arr, 0, n - 1);
}


/**************************************  三路快排   *********************************************************/

//将arr[l...r]分为<v;==v;>v 三部分
//之后递归对<v;>v两部分进行三路快排
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
    if(r-l<=15){
        InsertionSort(arr,l,r);
        return;
    }

    //partition
    swap(arr[l],arr[rand()%(r-l+1)+l]);
    T v = arr[l];

    int lt = l;    //arr[l+1...lt]<v, lt指向<v的最后一位, lt(less than)
    int gt = r+1;  //arr[gt...r]>v    gt指向>v的第一位, gt(greater than)
    int i = l+1;   //arr[l+1...i)==v  i指向待处理的元素

    while(i<gt){
        if(arr[i]<v){
            swap(arr[i],arr[lt+1]);
            lt++;
            i++;
        }
        else if(arr[i]>v){
            swap(arr[i],arr[gt-1]);
            gt--; //这里不需要进行i++，i指向交换过来的arr[gt-1]，这仍然是个未判断的值
        }
        else{//arr[i]==v
            i++;
        }
    }
    swap(arr[l],arr[lt]);  //arr[l]是等于v的，放在arr[lt]处，随后递归lt之前的部分，即lt-1

    // c++不方便返回一个区间的数，因此直接递归，不编写专门的partition函数
    __quickSort3Ways(arr,l,lt-1);  //这里容易出错，是递归lt之前的部分，即lt-1
    __quickSort3Ways(arr,gt,r);
}


template<typename T>
void quickSort3Ways(T arr[],int n){
    srand(time(NULL));
    __quickSort3Ways(arr,0,n-1);
}