#include <iostream>
#include <vector>
#include "Heap.h"

using namespace std;

void Heap::printArray()
{
	for (int element : arr)
	{
		cout << element << " ";
	}
}

//MAX HEAP
void Heap::max_heapify(vector<int>& arr, int n, int i)
{
	int left = 2 * i + 1;		//left child index
	int right = 2 * i + 2;		//right child index
	int largest = i;			//index of largest node of parent its child nodes

	//finds largest child node
	if (left<n && arr[left]>arr[largest])
		largest = left;
	if (right<n && arr[right]>arr[largest])
		largest = right;

	//if largest node is not the parent, swap with appropriate child node
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		max_heapify(arr, n, largest);
	}
}

void Heap::buildMaxHeap(vector<int>& arr, int n)
{
	for (int i = (n / 2 - 1); i >= 0; i--)	//run through entire heap and heapify
		max_heapify(arr, n, i);
}

void Heap::ascendingHeapSort(vector<int>& arr, int n)
{
	buildMaxHeap(arr, n);			//make arr into a max heap
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);		//swap nodes at root and i
		max_heapify(arr, i, 0);		//perform max heapify on arr of size i
	}
}

void Heap::insert_value_maxHeap(vector<int>& arr, int val)
{
	arr.push_back(val);
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		if (arr[i] > arr[(i - 1) / 2])		//if child is greater than parent
		{
			swap(arr[i], arr[(i - 1) / 2]);
			i = ((i - 1) / 2) + 1;			//set i to pos of new parent node + 1,
											//as for loop will decrement i
		}
	}
}

void Heap::modifyKeyMax(vector<int>& arr, int i, int val)
{
	arr[i] = val;
	while (i >= 0)
	{
		if (arr[i] > arr[(i - 1) / 2])		//if child is greater than parent
		{
			swap(arr[i], arr[(i - 1) / 2]);
			i = ((i - 1) / 2) + 1;			//set i to pos of new parent node + 1,
											//as for loop will decrement i
		}
		i--;
	}
}

int Heap::extract_maximum(vector<int>& arr)
{
	int max = arr[0];				//set max to root
	arr[0] = arr[arr.size() - 1];	//set root to last node
	arr.pop_back();					//remove last node
	max_heapify(arr, arr.size(), 0);//heapify
	return max;
}

//MIN HEAP
void Heap::min_heapify(vector<int>& arr, int n, int i)
{
	int left = 2 * i + 1;		//left child index
	int right = 2 * i + 2;		//right child index
	int smallest = i;			//index of smallest node of parent its child nodes

	//finds smallest child node
	if (left<n && arr[left]<arr[smallest])
		smallest = left;
	if (right<n && arr[right]<arr[smallest])
		smallest = right;

	//if smallest node is not the parent, swap with appropriate child node
	if (smallest != i)
	{
		swap(arr[i], arr[smallest]);
		min_heapify(arr, n, smallest);
	}
}

void Heap::buildMinHeap(vector<int>& arr, int n)
{
	for (int i = (n / 2 - 1); i >= 0; i--)	//run through entire heap and heapify
		min_heapify(arr, n, i);
}

void Heap::descendingHeapSort(vector<int>& arr, int n)
{
	buildMinHeap(arr, n);			//make arr into a min heap
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);		//swap nodes at root and i
		min_heapify(arr, i, 0);		//perform min heapify on arr of size i
	}
}

void Heap::insert_value_minHeap(vector<int>& arr, int val)
{
	arr.push_back(val);
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		if (arr[i] < arr[(i - 1) / 2])		//if child is less than parent
		{
			swap(arr[i], arr[(i - 1) / 2]);
			i = ((i - 1) / 2) + 1;			//set i to pos of new parent node + 1,
											//as for loop will decrement i
		}
	}
}

void Heap::modifyKeyMin(vector<int>& arr, int i, int val)
{
	arr[i] = val;
	while (i >= 0)
	{
		if (arr[i] < arr[(i - 1) / 2])		//if child is less than parent
		{
			swap(arr[i], arr[(i - 1) / 2]);
			i = ((i - 1) / 2) + 1;			//set i to pos of new parent node + 1,
											//as for loop will decrement i
		}
		i--;
	}
}

int Heap::extract_minimum(vector<int>& arr)
{
	int min = arr[0];				//set min to root
	arr[0] = arr[arr.size() - 1];	//set root to last node
	arr.pop_back();					//remove last node
	min_heapify(arr, arr.size(), 0);//heapify
	return min;
}