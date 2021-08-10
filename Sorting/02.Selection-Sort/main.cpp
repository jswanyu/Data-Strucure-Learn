#include<iostream>
#include<string>
#include "SortTestHelper.h"
#include "Student.h"
#include "SelectionSort.h"

using namespace std;
using namespace SortTestHelper;

void test01()
{
	int n = 100;
	int* a = generateRandomArray(n, 0, n);
	SelectionSort(a, n);
	printArray(a, n);
	delete[] a;
	cout << endl << endl;

	double b[] = { 4.4,3.3,2.2,1.1 };
	SelectionSort(b, 4);
	printArray(b, 4);
	cout << endl << endl;

	string c[] = { "d","c","b","a" };
	SelectionSort(c, 4);
	printArray(c, 4);
	cout << endl << endl;

	Student d[4] = { {"D",90},{"C",100},{"B",95},{"A",95} };
	SelectionSort(d, 4);
	printArray(d, 4);
	cout << endl << endl;
}

void test02()
{
	int n = 100000;
	int* a = generateRandomArray(n, 0, n);
	testSort("Selection Sort", SelectionSort, a, n);
	delete[] a;
}



int main() {
	test01();
	system("pause");
	return 0;
}