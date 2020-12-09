#include<iostream>
#include<time.h>
using namespace std;

void mergeSort(int[], int, int);	//sorts an arr using mergeSort
void merge(int[], int, int, int);	//merges two sorted arrs into one sorted arr
void printArr(int[], int);			//prints arr

int main()
{
	const int size = 50000;			//size of arrs for easy modification

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
	mergeSort(sortedArr, 0, size - 1);
	time = clock() - time;	//end time
	cout << "sortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

	time = clock();			//start time
	mergeSort(reverseSortedArr, 0, size - 1);
	time = clock() - time;	//end time
	cout << "reverseSortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

	time = clock();			//start time
	mergeSort(halfSortedArr, 0, size - 1);
	time = clock() - time;	//end time
	cout << "halfSortedArr execution time: " << (float)time / CLOCKS_PER_SEC << " seconds\n";

	return 0;
}

void mergeSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;		//calculate midpoint of arr
		mergeSort(arr, left, mid);			//call mergeSort on first half of arr
		mergeSort(arr, mid + 1, right);		//call mergeSort on second half of arr
		merge(arr, left, mid, right);		//merge first and second half of arr
	}
}

void merge(int arr[], int left, int mid, int right)
{
	int* newArr = new int[right - left + 1];	//stores newArr from merge
	int newArrIndex = 0;		//index of newArr for adding values
	int lIndex = left;		//index of left arr
	int rIndex = mid + 1;	//index of right arr

	//takes smallest value from each arr and places in newArr until end of an arr is hit
	while (!(lIndex == mid + 1 || rIndex == right + 1))
	{
		if (arr[lIndex] <= arr[rIndex])
		{
			//add new element to newArr and iterate indexes
			newArr[newArrIndex] = arr[lIndex];
			lIndex++;
			newArrIndex++;
		}
		else
		{
			//add new element to newArr and iterate indexes
			newArr[newArrIndex] = arr[rIndex];
			rIndex++;
			newArrIndex++;
		}
	}

	//copies remaining elements of non-empty arr to newArr (at most one while loop will execute)
	while (lIndex < mid + 1)
	{
		//add new element to newArr and iterate indexes
		newArr[newArrIndex] = arr[lIndex];
		lIndex++;
		newArrIndex++;
	}
	while (rIndex < right + 1)
	{
		//add element to newArr and iterate indexes
		newArr[newArrIndex] = arr[rIndex];
		rIndex++;
		newArrIndex++;
	}

	//overwrite old arr with newArr
	for (size_t i = 0; i < right - left + 1; i++)
		arr[left + i] = newArr[i];

	//memory management
	delete[] newArr;
	newArr = nullptr;
}

void printArr(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
		cout << arr[i] << " ";
}