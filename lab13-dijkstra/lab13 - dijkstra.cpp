//program to demonstrate dijkstras algorithm
#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class Graph
{
private:
	int size;
	void setSize(int argSize) { size = argSize; }
public:
	int** matrix;
	int getSize() { return size; }

	//set edge of graph
	void setEdge(int u, int v, int weight)
	{
		matrix[u][v] = weight;
	}

	//print graph matrix
	void print()
	{
		for (size_t i = 0; i < getSize(); i++)
		{
			for (size_t j = 0; j < getSize(); j++)
				cout << matrix[i][j] << '\t';
			cout << endl;
		}
	}

	//release memory used by object
	void cleanup()
	{
		for (size_t i = 0; i < getSize(); i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	Graph(int argSize)
	{
		setSize(argSize);	//set size of graph

		//init matrix to 0
		matrix = new int* [getSize()];
		for (size_t i = 0; i < getSize(); i++)
		{
			matrix[i] = new int[getSize()];
			for (size_t j = 0; j < getSize(); j++)
				matrix[i][j] = 0;
		}
	}
};

//function prototypes
void dijkstra(Graph G, int start);
int findClosestNode(Graph G, int distance[], bool visited[]);
void printSolution(Graph G, int distance[]);

int main()
{
	int size, start;
	cout << "Enter graph size: ";
	cin >> size;
	cin.ignore();
	cout << "Enter starting node: ";
	cin >> start;
	cin.ignore();
	cout << "Enter edges in format u,v,weight;u,v,weight;...;u,v,weight:";

	//build graph
	string input;
	getline(cin, input);

	Graph myGraph(size);

	stringstream inputs(input);
	while (inputs.good())
	{
		string u;
		string v;
		string weight;
		getline(inputs, u, ',');
		getline(inputs, v, ',');
		getline(inputs, weight, ';');

		myGraph.setEdge(stoi(u), stoi(v), stoi(weight));
	}
	cout << "\nGraph\n";
	myGraph.print();

	cout << endl;
	dijkstra(myGraph, start);
	return 0;
}

int findClosestNode(Graph G, int distance[], bool visited[])
{
	int min = INT_MAX;
	int index;
	for (size_t i = 0; i < G.getSize(); i++)
	{
		if(!visited[i] && distance[i] <= min)
		{
			min = distance[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(Graph G, int start)
{
	int* distance = new int[G.getSize()];	//keep track of distance from i
	bool* visited = new bool[G.getSize()];	//keep track of visited nodes

	for (size_t i = 0; i < G.getSize(); i++)
	{	//set all distances to inf, all nodes to not visited
		distance[i] = INT_MAX;
		visited[i] = false;
	}

	//set distance of starting node to 0 (so we know where to start)
	distance[start] = 0;

	//relax edge |V|-1 times
	for (size_t i = 0; i < G.getSize()-1; i++)
	{
		int u = findClosestNode(G, distance, visited);	//find next closest node
		visited[u] = true;	//mark u as visited
		for (size_t v = 0; v < G.getSize(); v++)
		{
			//update distance[i] if not visited and a shorter path is found
			if (!visited[v] &&				//not visited
				G.matrix[u][v] &&			//a connection exists
				distance[u] != INT_MAX &&	//distance is not inf
				distance[u] + G.matrix[u][v] < distance[v])	//shorter path
			{
				distance[v] = distance[u] + G.matrix[u][v];
			}
		}
	}

	printSolution(G, distance);
}

void printSolution(Graph G, int distance[])
{
	cout << "Source\tDistance\n";
	for (size_t i = 0; i < G.getSize(); i++)
	{
		if (distance[i] == INT_MAX)
			cout << i << "\tCannot reach from source!\n";
		else if (distance[i] == 0)
			cout << i << "\tStart\n";
		else
			cout << i << '\t' << distance[i] << endl;
	}
}