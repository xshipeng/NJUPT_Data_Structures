#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
template<class T>
void Swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
template<class T>
void SelectSort(T A[], int n) {
	for (int i = 0; i < n; i++) {
		int	min = i;
		for (int j = i + 1; j < n; j++)
			if (A[j] < A[min]) min = j;
		Swap(A[i], A[min]);
	}
}
template<class T>
void InsertSort(T A[], int n) {
	for (int i = 1; i < n; i++) {
		int	j = i;
		T temp = A[j];
		while (j > 0 && temp < A[j - 1]) {
			A[j] = A[j - 1];
			j--;
		}
		A[j] = temp;
	}
}
template<class T>
void BubbleSort(T A[], int n) {
	int i = n - 1;
	int last;
	while (i > 0) {
		last = 0;
		for (int j = 0; j < i; j++) {
			if (A[j + 1] < A[j]) {
				Swap(A[j + 1], A[j]);
				last = j;
			}
		}
		i = last;
	}
}
template<class T>
void QuickSort(T A[], int n) {
	QSort(A, 0, n - 1);
}
template<class T>
void QSort(T A[], int left, int right) {
	int i, j;
	if (left<right)
	{
		i = left;
		j = right + 1;
		do {
			do i++; while (A[i]<A[left]);
			do j--; while (A[j] > A[left]);
			if (i < j)
				Swap(A[i], A[j]);
		} while (i < j);
		Swap(A[left], A[j]);
		QSort(A, left, j - 1);
		QSort(A, j + 1, right);
	}
}
template<class T>
void Merge(T A[], int i1, int j1, int i2, int j2) {
	T *temp = new T[j2 - i1 + 1];
	int m = i1;
	int n = i2;
	int k = 0;
	while (m <= j1&&n <= j2)
		if (A[m] < A[n])temp[k++] = A[m++];
		else
			temp[k++] = A[n++];
	while (m <= j1)temp[k++] = A[m++];
	while (n <= j2)temp[k++] = A[n++];
	for (int i = 0; i <k; i++)
		A[i1++] = temp[i];
	delete[] temp;
}
template<class T>
void MergeSort(T A[], int n) {
	int i1, j1, i2, j2;
	int size = 1;
	while (size < n) {
		i1 = 0;
		while (i1 + size < n) {
			j1 = i1 + size - 1;
			i2 = j1 + 1;
			if (i2 + size - 1 < n)
				j2 = i2 + size - 1;
			else
				j2 = n - 1;
			Merge(A, i1, j1, i2, j2);
			i1 = j2 + 1;
		}
		size *= 2;
	}
}
template<class T>
void MagicSort(T A[], int n) {
	MSort(A, 0, n - 1);
}
template<class T>
void MSort(T A[], int left, int right) {
	int i, j;
	if (right - left + 1 <= 10)
		InsertSort(A + left, right - left + 1);
	else if (left<right)
	{
		i = left;
		j = right + 1;
		do {
			do i++; while (A[i]<A[left]);
			do j--; while (A[j] > A[left]);
			if (i < j)
				Swap(A[i], A[j]);
		} while (i < j);
		Swap(A[left], A[j]);
		MSort(A, left, j - 1);
		MSort(A, j + 1, right);
	}
}void main() {
	system("color f0"); 
	cout << "排序算法的结果验证：" << endl;
	int n = 15;
	double *arr1 = new double[n], *arr2 = new double[n], *arr3 = new double[n], *arr4 = new double[n], *arr5 = new double[n], *arr6 = new double[n];
	cout << "原序列：";
	for (int i = 0; i < n; i++) {
		arr1[i] = arr2[i] = arr3[i] = arr4[i] = arr5[i] = arr6[i] = rand();
		cout << arr1[i] << " ";
	}
	cout << endl;
	SelectSort(arr1, n);
	InsertSort(arr2, n);
	BubbleSort(arr3, n);
	QuickSort(arr4, n);
	MergeSort(arr5, n);
	MagicSort(arr6, n);
	cout << "简单选择排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr1[i] << " ";
	cout << endl;
	cout << "直接插入排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr2[i] << " ";
	cout << endl;
	cout << "冒泡排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr3[i] << " ";
	cout << endl;
	cout << "快速排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr4[i] << " ";
	cout << endl;
	cout << "两路合并排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr5[i] << " ";
	cout << endl;
	cout << "改进的快速排序后序列：";
	for (int i = 0; i < n; i++)
		cout << arr6[i] << " ";
	cout << endl;
	delete []arr1, arr2, arr3, arr4, arr5, arr6;
	cout << endl<<"排序算法的时间比较：" << endl;
	n = 40000;
	arr1 = new double[n], arr2 = new double[n], arr3 = new double[n], arr4 = new double[n], arr5 = new double[n], arr6 = new double[n];
	for (int i = 0; i < n; i++)
	{
		arr1[i] = arr2[i] = arr3[i] = arr4[i] = arr5[i] = arr6[i] = rand();
	}
	clock_t start, finish;
	start = clock();
	SelectSort(arr1, n);
	finish = clock();
	cout << "简单选择排序：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	InsertSort(arr2, n);
	finish = clock();
	cout << "直接插入排序时间：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	BubbleSort(arr3, n);
	finish = clock();
	cout << "冒泡排序时间：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	QuickSort(arr4, n);
	finish = clock();
	cout << "快速排序时间：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	MergeSort(arr5, n);
	finish = clock();
	cout << "两路合并排序时间：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	MagicSort(arr6, n);
	finish = clock();
	cout << "改进的快速排序时间：" << endl << "开始时间：" << start << "  结束时间：" << finish << "  持续时间：" << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	delete []arr1, arr2, arr3, arr4, arr5, arr6;
	char c = getchar();
}
