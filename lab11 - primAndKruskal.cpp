#include<iostream>
#include<string>
#include<sstream>

using namespace std;

//function prototypes


class Edge
{
private:
	int node;									//node edge is connecting to
	int weight;									//weight of edge
	Edge* next;									//next edge in adj matrix
	void setNode(int arg) { node = arg; }		//set node connection
	void setWeight(int arg) { weight = arg; }	//set weight of edge
public:
	void setNext(Edge* arg) { next = arg; }		//set next edge
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
	Edge** adjMatrix;
	void setSize(int arg) { size = arg; }
	void setAdjMatrix(Edge** arg) { adjMatrix = arg; }
public:
	int getSize() { return size; }

	void printGraph()
	{
		cout << '\t';
		for (size_t i = 0; i < size; i++)
			cout << i << '\t';
		cout << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << i << '\t';
			Edge* cur = adjMatrix[i];
			while (cur != nullptr)
			{
				cout << cur->getWeight() << '\t';
				cur = cur->getNext();
			}
			cout << endl;			
		}
	}

	//constructor and destructor
	Graph(int argSize, Edge** argAdjMatrix)
	{
		setSize(argSize);
		setAdjMatrix(argAdjMatrix);
	}
	~Graph()
	{
		for (size_t i = 0; i < size; i++)
		{
			Edge* cur = adjMatrix[i];
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
	string strSize;
	//get size of graph from user
	cout << "Enter size of graph: ";
	getline(cin, strSize);
	int size = stoi(strSize);
	Edge** adjMatrix = new Edge*[size];
	
	//get adj matrix from user line by line
	for (size_t i = 0; i < size; i++)
	{
		Edge* HEAD = new Edge(0, 0);
		Edge* cur = HEAD;
		cout << "Enter weights for node " << i << " (comma-delimited, inf for "
			<< "no connection): ";
		string input;
		getline(cin, input);
		stringstream ssWeights(input);
		while (ssWeights.good())
		{
			//traverse the string settings building the adjacency matrix
			string weight;
			getline(ssWeights, weight, ',');
			if (weight == "inf")
				cur->setNext(new Edge(i, int(INFINITY)));
			else
				cur->setNext(new Edge(i, stoi(weight)));
			cur = cur->getNext();
		}
		adjMatrix[i] = HEAD->getNext();
		delete HEAD;
	}

	Graph myGraph(size, adjMatrix);
	myGraph.printGraph();

	return 0;
}