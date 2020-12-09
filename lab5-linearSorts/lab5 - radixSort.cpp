#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>

using namespace std;

void radixSort(int[], int);		//sort an array using radix sort
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
	radixSort(arr, arrSize);
	time_req = clock() - time_req;	//end time
	cout << "Sorted arr: ";
	printArr(arr, arrSize);
	cout << "\nTime for radixSort: " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;

	system("PAUSE");
	return 0;
}

void radixSort(int inputArr[], int size)
{
	int max = inputArr[0];
	for (size_t i = 1; i < size; i++)			//find max element
	{
		if (inputArr[i] > max)
			max = inputArr[i];
	}

	int digitPos = 1;
	while (max /= 10)							//find length of max
		digitPos++;

	for (size_t i = 0; i < digitPos; i++)
	{
		int* auxArr = new int[10];
		for (size_t j = 0; j < 10; j++)			//create auxArr with elements init to 0
			auxArr[j] = 0;
		
		for (size_t j = 0; j < size; j++)		//inc auxArr for elements in digit column
			auxArr[(inputArr[j] / (int)pow(10, i)) % 10]++;

		for (size_t j = 1; j < 10; j++)			//cumulatively add values of auxArr
			auxArr[j] += auxArr[j - 1];
	
		int* sortedArr = new int[size];			//array to sort values into

		for (int j = size - 1; j >= 0; j--)		//inc backwards through inputArr
		{
			int index = --auxArr[(inputArr[j] / (int)pow(10, i)) % 10];	//find element in auxArr corresponding to
																		//cur digit in cur inputArr, dec and store in index
			sortedArr[index] = inputArr[j];		//store curr inputArr in sortedArr at index
		}

		for (size_t j = 0; j < size; j++)
			inputArr[j] = sortedArr[j];
	}
}

void printArr(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
		cout << arr[i] << " ";
}