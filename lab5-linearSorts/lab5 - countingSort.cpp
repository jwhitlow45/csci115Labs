#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

void countingSort(int[], int);	//sort an array using counting sort
void printArr(int[], int);		//print an array

int main()
{
	clock_t time_req;
	srand(time(NULL));		//seed rng
	const int arrSize = 10;
	int arr[arrSize];
	for (size_t i = 0; i < arrSize; i++)
		arr[i] = rand() % 10;
	
	cout << "Unsorted arr: ";
	printArr(arr, arrSize);
	cout << endl;
	time_req = clock();				//start time
	countingSort(arr, arrSize);
	time_req = clock() - time_req;	//end time
	cout << "Sorted arr: ";
	printArr(arr, arrSize);
	cout << "\nTime for countingSort: " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;

	system("PAUSE");
	return 0;
}

void countingSort(int inputArr[], int size)
{
	int max = inputArr[0];
	for (size_t i = 1; i < size; i++)		//find max element
	{
		if (inputArr[i] > max)
			max = inputArr[i];
	}

	int* auxArr = new int[max + 1];			//create auxArr of size max + 1 and initialize to 0
	for (size_t i = 0; i < max + 1; i++)
		auxArr[i] = 0;

	for (size_t i = 0; i < size; i++)		//store count of each element in auxArr
		auxArr[inputArr[i]]++;

	for (size_t i = 1; i < max + 1; i++)	//cumulatively add values of auxArr
		auxArr[i] += auxArr[i - 1];

	int* sortedArr = new int[size];			//new arr to sort input arr into

	for (int i = size - 1; i >= 0; i--)		//loop from end of input arr
	{
		int index = --auxArr[inputArr[i]];	//store index for inputArr[i] to be stored in sortedArr, dec index
		sortedArr[index] = inputArr[i];		//place inputArr[i] in proper index in sortedArr
	}

	for (size_t i = 0; i < size; i++)		//overwrite arr
		inputArr[i] = sortedArr[i];

	//memory management
	delete[] auxArr;
	auxArr = nullptr;
	delete[] sortedArr;
	sortedArr = nullptr;
}

void printArr(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
		cout << arr[i] << " ";
}