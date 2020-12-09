#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Graph
{
private:
	int numV;
	int numE;

	void setNumV(int arg) { numV = arg; }
	void setNumE(int arg) { numE = arg; }
public:
	int getNumV() { return numV; }
	int getNumE() { return numE; }
	int** edgeMatrix;

	void cleanup()
	{
		for (size_t i = 0; i < getNumE(); i++)
			delete[] edgeMatrix[i];
		delete[] edgeMatrix;
	}

	Graph(int argV, int argE)
	{
		setNumV(argV);
		setNumE(argE);
		edgeMatrix = new int*[getNumE()];
		for (size_t i = 0; i < numE; i++)
		{
			int* row = new int[3];
			edgeMatrix[i] = row;
		}
	}
};

//function prototypes
void bellmanFord(Graph G, int startNode);

int main()
{
	int numVertex;		//number of vertices in the graph
	int numEdge;		//number of edges in the graph
	int startVertex;	//starting vertex

	string edges;

	cout << "Enter number of vertices: ";
	cin >> numVertex;
	cin.ignore();
	cout << "Enter number of edges: ";
	cin >> numEdge;
	cin.ignore();
	Graph* myGraph =  new Graph(numVertex, numEdge);
	cout << "Enter starting vertex: ";
	cin >> startVertex;
	cin.ignore();
	cout << "Enter edges in format v1,v2,weight;...;v1,v2,weight: ";
	getline(cin, edges);

	//handle user input and store in appropriate place in edge matrix
	stringstream sEdges(edges);
	int i = 0;	//keep track of edge number
	while (sEdges.good())
	{
		string v1, v2, weight;			//start node, finish node, edge weight
		getline(sEdges, v1, ',');		//get starting node
		getline(sEdges, v2, ',');		//get finishing node
		getline(sEdges, weight, ';');	//get edge weight
		//store retrieved values into edge matrix in Graph
		myGraph->edgeMatrix[i][0] = stoi(v1);
		myGraph->edgeMatrix[i][1] = stoi(v2);
		myGraph->edgeMatrix[i][2] = stoi(weight);
		i++;
	}
	//check if sufficient number of edges were entered
	if (i < numEdge || i > numEdge)
	{
		cout << "ERROR:Invalid number of edges entered.";
		return 0;
	}

	//run BellmanFord algorithm
	bellmanFord(*myGraph, 0);
	myGraph->cleanup();
	delete myGraph;
	return 0;
}

void bellmanFord(Graph G, int startNode)
{
	//array to store distance from source to rest of vertex
	int* distanceList = new int[G.getNumV()];
	//instantiate distance list to inf, start node is 0
	for (size_t i = 0; i < G.getNumV(); i++)
		distanceList[i] = INT_MAX;
	distanceList[startNode] = 0;

	//iterate v-1 times
	for (size_t i = 0; i < G.getNumV() - 1; i++)
	{
		for (size_t j = 0; j < G.getNumE(); j++)
		{	//look for shorter path between nodes
			int v1 = G.edgeMatrix[j][0];
			int v2 = G.edgeMatrix[j][1];
			int w = G.edgeMatrix[j][2];
			if (distanceList[v1] + w < distanceList[v2])
				distanceList[v2] = distanceList[v1] + w;
		}
	}

	//check for negative weight cycles
	for (size_t j = 0; j < G.getNumE(); j++)
	{
		int v1 = G.edgeMatrix[j][0];
		int v2 = G.edgeMatrix[j][1];
		int w = G.edgeMatrix[j][2];
		if (distanceList[v1] + w < distanceList[v2])
		{
			cout << "ERROR: Graph contains a negative weight cycle.";
			return;
		}
	}

	//print out distance from source to each vertex
	cout << "Vertex\t\tDistance from source vertex" << endl;
	for (size_t i = 0; i < G.getNumV(); i++)
	{
		cout << i << "\t\t" << distanceList[i] << endl;
	}

	delete[] distanceList;
}