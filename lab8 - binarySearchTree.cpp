#include<iostream>
#include"List.h"

using namespace std;

int main()
{
	const int arrSize = 7;
	BST myTree;
	int arr[arrSize] = { 27,14,35,10,19,31,42 };
	int userSearchNum;
	char userSearchAgain;
	
	//populate tree and tree input
	cout << "Inserted elements: ";
	for (size_t i = 0; i < arrSize; i++)
	{
		cout << arr[i] << " ";
		myTree.insertNode(myTree.getRoot(), arr[i]);
	}
	cout << endl << "Post order: ";
	myTree.printTree(myTree.getRoot());
	cout << "\nLargest element: " << myTree.largest(myTree.getRoot()) << endl;
	
	do
	{
		cout << "Insert element to search for: ";
		cin >> userSearchNum;
		cin.ignore();
		if (myTree.findNode(myTree.getRoot(), userSearchNum))
			cout << userSearchNum << " found in the tree!";
		else
			cout << userSearchNum << " not found in the tree!";
		cout << "\nSearch again?(y/n): ";
		cin >> userSearchAgain;
	} while (tolower(userSearchAgain) == 'y');

	return 0;
}