#include<iostream>
#include<time.h>
using namespace std;

int fibSeq(int);	//recursively calculates the fibonacci sequence

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
	//base case
	if (n == 1)
		return 1;
	if (n == 0)
		return 0;

	//recursive case
	return fibSeq(n - 1) + fibSeq(n - 2);
}