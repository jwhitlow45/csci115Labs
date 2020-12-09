//Jacob Whitlow
//Lab1-StacksLinkedLists-Part1

#include<iostream>

using namespace std;

class Stack
{
private:	
	int top = -1;				//position of the top of the stack
	int arrStack[10];			//array stack
public:
	void push(int);	//adds a value to the top of the stack
	int pop();		//removes a value from the top of the stack and returns it
	int peek();		//returns the top value of the stack
	void print();	//prints the stack

	bool isEmpty();	//returns if stack is empty
	bool isFull();		//returns if stack is full
};


int main()
{
	Stack myStack;		//instantiate stack
	
	myStack.push(20);	//push integers to the stack
	myStack.push(40);
	myStack.push(60);
	
	cout << "Items in the stack: ";
	myStack.print();
	cout << endl;

	cout << "Popped item is: " << myStack.pop() << endl;
	cout << "Peeked item is: " << myStack.peek() << endl;

	cout << "Items in the stack: ";
	myStack.print();
	cout << endl;
}

//Stack Method Definitions
void Stack::push(int value)
{
	if (isFull())
	{
		cout << "ERROR: STACK OVERFLOW" << endl; //error message
		return;
	}
	top++;							//increment top
	arrStack[top] = value;			//set top equal to pushed value
}

int Stack::pop()
{
	if (isEmpty())	//if stack is empty
	{
		cout << "ERROR: STACK UNDERFLOW" << endl;	//error message
		return NULL;
	}

	int poppedValue = arrStack[top];	//store popped value for return before deletion
	arrStack[top] == NULL;			//set value in stack equal to NULL
	top--;							//decrement top
	return poppedValue;
}

int Stack::peek()
{
	if (isEmpty())	//if stack is empty
	{
		cout << "ERROR: STACK UNDERFLOW" << endl;	//error message
		return NULL;
	}
	
	return arrStack[top];
}

void Stack::print()
{
	if (isEmpty())	//if stack is empty
	{
		cout << "ERROR: STACK UNDERFLOW" << endl;	//error message
		return;
	}

	for (size_t i = 0; i < top; i++)		//iterates through values from 0 to top - 1
		cout << arrStack[top - i] << ", ";	//prints out values starting at top down to 1 above bottom
	cout << arrStack[0];					//prints last element that is not printed in for loop
}

bool Stack::isEmpty()
{
	return top < 0;
}

bool Stack::isFull()
{
	return top >= 9;
}