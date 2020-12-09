//Jacob Whitlow
//Lab1-StacksLinkedLists-Part2
#include<iostream>

using namespace std;

struct Node
{
	Node* next;
	int data;
};

struct LinkedList
{
private:
	Node* head = nullptr;
public:
	void insert(int);		//insert at beginning of linked list
	void pop_front();		//remove element from front of linked list
	void pop_back();		//remove element from end of linked list
	void print();			//display contents of the linked list

	bool isEmpty();			//returns if linked list is empty
};

int main()
{
	LinkedList myLinkedList;	//instantiate linked list

	myLinkedList.insert(60);	//insert values into list
	myLinkedList.insert(40);
	myLinkedList.insert(20);

	cout << "Items in the linked list: ";
	myLinkedList.print();
	cout << endl;

	myLinkedList.pop_front();
	cout << "Items in the linked list after deleting the first element: ";
	myLinkedList.print();
	cout << endl;

	myLinkedList.pop_back();
	cout << "Items in the linked list after deleting the last element: ";
	myLinkedList.print();
	cout << endl;
}

//LinkedList Method Definitions
void LinkedList::insert(int value)
{
	Node* tempPtr = new Node();	//instantiate new node
	tempPtr->data = value;		//set data of new node
	tempPtr->next = head;		//set next of new node to head
	head = tempPtr;				//make new node head
}

void LinkedList::pop_front()
{
	if (isEmpty())
	{
		cout << "ERROR: LINKED LIST IS EMPTY";	//error message
		return;
	}

	Node* tempPtr = head;	//copy head so head can be moved
	head = head->next;		//head moved to next in list (new head)
	delete tempPtr;			//delete old head
	tempPtr = nullptr;		//clean hanging pointer
}

void LinkedList::pop_back()
{
	if (isEmpty())
	{
		cout << "ERROR: LINKED LIST IS EMPTY";	//error message
		return;
	}
	Node* curPtr = head;			//make curPtr beginning of linked list
	
	if (curPtr->next == nullptr)	//check if there is only one node in the list
	{
		delete curPtr;	//delete only node in list
		head = nullptr;	//clean up hanging pointer
		return;
	}

	while (curPtr->next->next != nullptr)	//iterate to second to last item in list
	{
		curPtr = curPtr->next;
	}
	delete curPtr->next;	//delete last item in list
	curPtr->next = nullptr;	//clean up hanging pointer
}

void LinkedList::print()
{
	if (isEmpty())
	{
		cout << "ERROR: LINKED LIST IS EMPTY";	//error message
		return;
	}
	
	Node* curPtr = head;				//get start of list
	while (curPtr->next != nullptr)		//while not last item in list
	{
		cout << curPtr->data << ", ";	//print out data of curPtr
		curPtr = curPtr->next;			//iterate curPtr
	}
	cout << curPtr->data;				//print out last remaining item in list
}

bool LinkedList::isEmpty()
{
	return head == nullptr;
}