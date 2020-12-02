#include<iostream>
#include<string>
#include<sstream>
#include<queue>
using namespace std;

class Graph
{
private:
	int size;
public:
	int** matrix;

	int getSize() { return size; }

	Graph(int argSize)
	{
		size = argSize;
		matrix = new int* [size];
		for (size_t i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
			for (size_t j = 0; j < size; j++)
				matrix[i][j] = 0;
		}
	}
};

//function prototypes
void primsMST(Graph G, int startNode);	//prims mst algorithm
void printMatrix(int** matrix, int size);		//print matrix
void printMST(int* parentList, int size);		//print mst

int main()
{
	string userSize;
	cout << "Enter size of graph: ";
	getline(cin, userSize);
	Graph myGraph(stoi(userSize));

	cout << "Enter weights for edges in format weight,weight,...\n";
	cout << "(0 for no connection)\n";
	for (size_t i = 0; i < stoi(userSize); i++)
	{
		string input;
		cout << "Node " << i << " weights: ";
		getline(cin, input);
		stringstream inputs(input);

		int* row = new int[stoi(userSize)];
		int j = 0;
		while (inputs.good())
		{
			string weight;
			getline(inputs, weight, ',');
			row[j] = stoi(weight);
			j++;
		}
		myGraph.matrix[i] = row;
	}

	primsMST(myGraph, 0);


	return 0;
}



void primsMST(Graph G, int startNode)
{
	//initialize starting lists and output matrix
	int* parentList = new int[G.getSize()];
	int* keyList = new int[G.getSize()];
	bool* vertexList = new bool[G.getSize()];
	
	for (size_t i = 0; i < G.getSize(); i++)
	{
		keyList[i] = 0;
		vertexList[i] = false;
	}
	keyList[startNode] = 0;
	parentList[startNode] = -1;

	//for every vertex
	for (size_t i = 0; i < G.getSize() - 1; i++)
	{
		//find min key of key list
		int u;	//index of minimum

		int smallest = INT_MAX;
		for (size_t v = 0; v < G.getSize(); v++)
		{
			if (vertexList[v] == false && smallest > keyList[v])
			{
				u = v;
			}
		}
		vertexList[u] = true;

		for (size_t v = 0; v < G.getSize(); v++)
		{	//update weights for each node adj to u
			if (G.matrix[u][v] != 0 &&
				vertexList[v] == false &&
				G.matrix[u][v] < keyList[v])
			{
				parentList[v] = u;
				keyList[v] = G.matrix[u][v];
			}
		}
	}

	cout << endl;
	printMST(parentList, G.getSize());
	cout << endl;

	delete[] parentList;
	delete[] vertexList;
	delete[] keyList;
}

void printMST(int* parentList, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << i << ":" << parentList[i] << " ";
	}
}


void printMatrix(int** matrix, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
