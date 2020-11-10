#include<iostream>
#include<time.h>

using namespace std;

void selectionSort(int[], int);	//sorts arr using selectionSort
void printArr(int[], int);		//prints arr

int main()
{
	const int size = 50000;		//size of arrs for easy modification

	//create and populate sorted array
	int sortedArr[size];
	for (size_t i = 0; i < size; i++)
		sortedArr[i] = i;

	//create and populate reverse sorted array
	int reverseSortedArr[size];
	for (size_t i = 0; i < size; i++)
		reverseSortedArr[i] = size - i;

	//create and populate half sorted array
	int halfSortedArr[size];
	for (size_t i = 0; i < size; i++)
	{
		if (i < size / 2)
			halfSortedArr[i] = i;
		else
			halfSortedArr[i] = size - i;
	}

	clock_t time;			//keeps track of execution time

	time = clock();			//start time
	selectionSort(sortedArr, size);
	time = clock() - time;	//end time
	cout << "sortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

	time = clock();			//start time
	selectionSort(reverseSortedArr, size);
	time = clock() - time;	//end time
	cout << "reverseSortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

	time = clock();			//start time
	selectionSort(halfSortedArr, size);
	time = clock() - time;	//end time
	cout << "halfSortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

}

void selectionSort(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		int* min = &arr[i];		//set first value in unsorted arr as min
		for (size_t j = i; j < size; j++)
		{
			if (*min > arr[j])	//set new min if cur element is less than min
				min = &arr[j];
		}
		//swap first and min element of unsorted array
		int temp = arr[i];
		arr[i] = *min;			
		*min = temp;			
	}
}

void printArr(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}
