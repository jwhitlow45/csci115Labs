#include<iostream>
#include<time.h>
using namespace std;

int fibSeq(int);	//iteratively calculates the fibonacci sequence

int main()
{
	clock_t time;	//keeps track of execution time
	int nPos;		//pos n to find of Fibonacci sequence

	cout << "Enter nth pos to find in Fibonacci sequence: ";
	cin >> nPos;

	time = clock();			//start time

	cout << "Number at pos " << nPos << ": " << fibSeq(nPos) << endl;

	time = clock() - time;	//end time

	cout << "Time to calculate: " << (float)time / CLOCKS_PER_SEC << " seconds" << endl;
}

int fibSeq(int n)
{
	int prev = 0, cur = 1, next = 1;	//prev = f(0), cur = f(1)

	if (n == 0)
		return 0;

	for (size_t i = 0; i < n - 1; i++)
	{
		next = cur + prev;	//next element is sum oof previous two
		prev = cur;			//iterate prev to cur pos
		cur = next;			//iterate cur to next pos
	}
	return next;
}