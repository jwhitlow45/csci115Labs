#include<iostream>
#include<string>

using namespace std;

class Edge
{
private:
	int node;									//node edge is connecting to
	int weight;									//weight of edge
	Edge* next;									//next edge in adj matrix
	void setNode(int arg) { node = arg; }		//set node connection
	void setWeight(int arg) { weight = arg; }	//set weight of edge
	void setNext(Edge* arg) { next = arg; }		//set next edge
public:
	int getNode() { return node; }				//get node connection
	int getWeight() { return weight; }			//get weight
	Edge* getNext() { return next; }

	//constructors
	Edge(int argNode, int argWeight)
	{
		setNode(argNode);
		setWeight(argWeight);
		setNext(nullptr);
	}
	Edge(int argNode, int argWeight, Edge* argNext)
	{
		setNode(argNode);
		setWeight(argWeight);
		setNext(argNext);
	}
};

class Graph
{
private:
	int size;
	Edge* adjMatrix;
	void setSize(int arg) { size = arg; }
	void setAdjMatrix(Edge* arg) { adjMatrix = arg; }
public:
	int getSize() { return size; }

	void printGraph()
	{
		for (size_t i = 0; i < size; i++)
			cout << '\t' << i << '\t';
		for (size_t i = 0; i < size; i++)
		{
			cout << i << '\t';
			Edge* cur = &adjMatrix[i];
			if (cur->getNode() > size)
				cout << "i\t";
			else
				cout << cur->getNode();			
		}
	}

	Graph(int argSize, Edge* argAdjMatrix)
	{
		setSize(argSize);
		setAdjMatrix(argAdjMatrix);
	}
	~Graph()
	{
		for (size_t i = 0; i < size; i++)
		{
			Edge* cur = &adjMatrix[i];
			Edge* next = cur;
			while (cur != nullptr)
			{
				next = next->getNext();
				delete cur;
				cur = next;
			}
			delete[] adjMatrix;
		}
	}
};

int main()
{
	return 0;
}