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
void primsMST(Graph G, int startNode);			//prims mst algorithm
void kruskalsMST(Graph G, int startNode);		//kruskals mst algorithm
void printMatrix(int** matrix, int size);		//print matrix
void printMST(Graph G, int* parentList, int size);		//print mst

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

		//build matrix from user input
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
	int* parents = new int[G.getSize()];
	int* keys = new int[G.getSize()];
	bool* vertices = new bool[G.getSize()];
	
	for (size_t i = 0; i < G.getSize(); i++)
	{
		keys[i] = INT_MAX;
		vertices[i] = false;
	}
	keys[startNode] = 0;		//set start node key to 0 to init start
	parents[startNode] = -1;	//set parent of start node to -1 as it is root

	//for every vertex
	for (size_t i = 0; i < G.getSize() - 1; i++)
	{
		//find min key of key list
		int u;	//index of minimum

		int smallest = INT_MAX;
		for (size_t v = 0; v < G.getSize(); v++)
		{
			if (vertices[v] == false && keys[v] < smallest)
			{
				u = v;
				smallest = keys[v];
			}
		}
		vertices[u] = true;

		for (size_t v = 0; v < G.getSize(); v++)
		{	//update weights for each node adj to u
			if (G.matrix[u][v] &&
				vertices[v] == false &&
				G.matrix[u][v] < keys[v])
			{
				parents[v] = u;
				keys[v] = G.matrix[u][v];
			}
		}
	}

	cout << endl;
	printMST(G, parents, G.getSize());
	cout << endl;

	delete[] parents;
	delete[] vertices;
	delete[] keys;
}

int kruskalFind(int* parents, int u)
{
	while (parents[u] != u)
		u = parents[u];
	return u;
}

void kruskalUnion(int* parents, int u, int v)
{
	int v1 = kruskalFind(parents, u);
	int v2 = kruskalFind(parents, v);
	if (v1 != v2)
		parents[v1] = v2;
}

bool kruskalUnionFind(int* parents, int u, int v, int size)
{
	if (parents[u] != parents[v])
	{
		int parU = parents[u];
		int parV = parents[v];
		for (size_t i = 0; i < size; i++)
		{
			if (parents[i] == parV)
				parents[i] = parU;
		}
		return true;
	}
	return false;
}

void kruskalsMST(Graph G, int startNode)
{
	int* parents = new int[G.getSize()];

	//set each node as its own parents
	for (size_t u = 0; u < G.getSize(); u++)
		parents[u] = u;

	int minimum = INT_MAX;	//minimum weight of graph
	int minU;				//u of minimum
	int minV;				//v of minimum
	for (size_t i = 0; i < G.getSize(); i++)
	{
		for (size_t u = 0; u < G.getSize(); u++)
		{
			for (size_t v = 0; v < u; v++)
			{
				if (minimum > G.matrix[u][v])
				{
					minimum = G.matrix[u][v];
					minU = u;
					minV = v;
				}
			}
		}
		if(kruskalUnionFind(parents, minU, minV, G.getSize()))
			kruskalUnion(parents, minU, minV);
	}

	cout << endl;
	printMST(G, parents, G.getSize());
	cout << endl;

	delete[] parents;
}

void printMST(Graph G, int* parentList, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (parentList[i] == j || parentList[j] == i)
				cout << G.matrix[i][j] << ' ';
			else
				cout << "x ";
		}
		cout << endl;
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
