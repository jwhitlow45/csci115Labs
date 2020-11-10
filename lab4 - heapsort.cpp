#include<iostream>
#include<vector>
#include<string>
#include"Heap.h"

using namespace std;

int main()
{
	char userOrder;		//order user wants heap in
	string userArr;		//for storing user arr input
	int userElement;	//element to add to heap
	Heap myHeap;

	cout << "Ascending or descending order?(a/d): ";		//get heap order from user
	cin >> userOrder;
	cin.ignore();

	cout << "Input array (space separated): ";				// get array from user
	getline(cin, userArr);

	string intBuffer = "";									//buffer for building int while reading string
	for (size_t i = 0; i < userArr.size(); i++)				//read through string and extract ints, adding them to the arr
	{
		intBuffer.push_back(userArr[i]);
		if (userArr[i] == ' ')
		{
			myHeap.arr.push_back(stoi(intBuffer));
			intBuffer = "";
		}
	}
	if (intBuffer != "")									//add left over int to arr
	{
		myHeap.arr.push_back(stoi(intBuffer));
	}

	cout << "Input element to insert: ";					//get element to input to the heap from user
	cin >> userElement;
	cin.ignore();	
	
	if (userOrder == 'a')		//perform ascending heap operations
	{
		myHeap.buildMaxHeap(myHeap.arr, myHeap.arr.size());
		myHeap.insert_value_maxHeap(myHeap.arr, userElement);
		myHeap.ascendingHeapSort(myHeap.arr, myHeap.arr.size());
		cout << "Sorted heap: ";
		myHeap.printArray();
		int max = myHeap.extract_maximum(myHeap.arr);
		cout << "\nOn calling extract_maximum: " << max << endl;
		cout << "Sorted heap is now: ";
		myHeap.ascendingHeapSort(myHeap.arr, myHeap.arr.size());
		myHeap.printArray();
		cout << endl;
	}
	else if (userOrder == 'd')	//perform descending heap operations
	{
		myHeap.buildMinHeap(myHeap.arr, myHeap.arr.size());
		myHeap.insert_value_minHeap(myHeap.arr, userElement);
		myHeap.descendingHeapSort(myHeap.arr, myHeap.arr.size());
		cout << "Sorted heap: ";
		myHeap.printArray();
		int min = myHeap.extract_minimum(myHeap.arr);
		cout << "\nOn calling extract_minimum: " << min << endl;
		cout << "Sorted heap is now: ";
		myHeap.descendingHeapSort(myHeap.arr, myHeap.arr.size());
		myHeap.printArray();
		cout << endl;
	}

	system("PAUSE");
	return 0;
}