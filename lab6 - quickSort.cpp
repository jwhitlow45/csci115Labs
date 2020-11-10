#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>

using namespace std;

int partition(int[], int, int);				//partition for quicksort
void quicksort(int[], int, int);			//sort an array using quicksort
int medianPartition(int[], int, int);		//partition for median quicksort
void medianQuicksort(int[], int, int);		//median pivot quicksort
int randomizedPartition(int[], int, int);	//partition for randomized quicksort
void randomizedQuicksort(int[], int, int);	//randomized pivot quicksort

int medianOfThree(int[], int, int, int);	//get median of three elements of an array,
												//sort them, and then insert into respective indicies
void printArr(int[], int);					//print arr for testing

int main()
{
	srand(time(NULL));							//seed rng
	const int arrSize = 10;						//size of arr
	int arr[arrSize] = { 0,2,9,5,4,3,7,6,1,8 };	//array to be sorted
	int partitionType;							//type of partition to perform on quicksort

	cout << "QUICKSORT\n0 - first element\n1 - random\n2 - median\nMethod for pivot?: ";
	cin >> partitionType;
	cin.ignore();
	//partitionType
		//0 - first element quicksort
		//1 - random element quicksort
		//2 - median element quicksort

	cout << "Original array: ";
	printArr(arr, arrSize);
	switch (partitionType)
	{
	case 0:
		quicksort(arr, 0, arrSize - 1);
		break;
	case 1:
		randomizedQuicksort(arr, 0, arrSize - 1);
		break;
	case 2:
		medianQuicksort(arr, 0, arrSize - 1);
		break;
	}
	cout << endl << "Sorted array: ";
	printArr(arr, arrSize);
	cout << endl;

	system("PAUSE");
	return 0;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[low];

	int i = low - 1;	//set i to pos before the arr
	int j = high + 1;	//set j to pos after the arr
	while (true)
	{
		do 
			j--;
		while (arr[j] > pivot);		//dec j til pivot
		do
			i++;
		while (arr[i] < pivot);		//inc i til pivot
		if (i < j)
			swap(arr[i], arr[j]);	//swap arr[i] and arr[j] if i < j
		else
			return j;				//return the found partition
	}
}
void quicksort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);		//get partition
		quicksort(arr, p, q);				//perform quicksort based on partition
		quicksort(arr, q + 1, r);
	}
}

int medianPartition(int arr[], int low, int high)
{
	int pivot = medianOfThree(arr, low, (high + low) / 2, high);

	int i = low - 1;	//set i to pos before the arr
	int j = high + 1;	//set j to pos after the arr
	while (true)
	{
		do
			j--;
		while (arr[j] > pivot);		//dec j til pivot
		do
			i++;
		while (arr[i] < pivot);		//inc i til pivot
		if (i < j)
			swap(arr[i], arr[j]);	//swap arr[i] and arr[j] if i < j
		else
			return j;				//return the found partition
	}
}
void medianQuicksort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = medianPartition(arr, p, r);			//get median partition
		medianQuicksort(arr, p, q);					//perform quicksort based on median partition
		medianQuicksort(arr, q + 1, r);
	}
}
int medianOfThree(int arr[], int low, int mid, int high)
{
	//first two if statements are xor that determine if low or high are the mid values
	if ((arr[low] > arr[high]) != (arr[low] > arr[mid]))		//check if low is the mid value
		swap(arr[low], arr[mid]);		//swap to make arr[low] the mid value
	else if ((arr[high] > arr[low]) != (arr[high] > arr[mid]))	//check if high is the mid value
		swap(arr[high], arr[mid]);		//swap to make arr[high] the mid value
	if (arr[low] > arr[high])
		swap(arr[low], arr[high]);
	return arr[mid];
}

int randomizedPartition(int arr[], int low, int high)
{
	int pivot = rand() % (high - low + 1) + low;	//find random pivot within arr range
	swap(arr[low], arr[pivot]);						//swap pivot with first element in the array
	return partition(arr, low, high);				//partition array using random pivot
}
void randomizedQuicksort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = randomizedPartition(arr, p, r);		//get random partition
		randomizedQuicksort(arr, p, q );			//perform quicksort based on random partition
		randomizedQuicksort(arr, q + 1, r);
	}
}

void printArr(int arr[], int size)
{
	for (size_t i = 0; i < size; i++)
		cout << arr[i] << " ";
}