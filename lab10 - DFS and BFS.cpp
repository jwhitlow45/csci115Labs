//program to implement depth first search and breadth first search
#include<iostream>
#include<string>
#include<sstream>
#include<queue>
using namespace std;

class Node
{
public:
	Node* next;
	int val;

	Node(int argVal, Node* argNext)
	{
		val = argVal;
		next = argNext;
	}
};

class Graph
{
private:
	int numNodes;
	Node* adjList[10];
	void setNumNodes(int arg) { numNodes = arg; }
	void setAdjList(Node* arg[])
	{
		for (size_t i = 0; i < 10; i++)
		{
			adjList[i] = arg[i];
		}
	}
public:

	int getNumNodes() { return numNodes; }
	Node* getAdjList(int index) { return adjList[index]; }

	void DFS_util(bool[], int);
	void DFS(int);

	void BFS(int);

	//constructor
	Graph(int argNumNodes, Node* argAdjList[]);
};

int main()
{
	int numNodes;		//number of nodes in graph
	int startNode;		//node to start DFS/BFS from
	Node* adjList[10];	//adj list to build to store in Graph object
	for (size_t i = 0; i < 10; i++)
		adjList[i] = nullptr;

	//get user num nodes
	cout << "Enter number of nodes (max 10): ";
	cin >> numNodes;
	numNodes = min(10, numNodes);
	cin.ignore();

	//get user adj list
	for (size_t i = 0; i < numNodes; i++)
	{	//get adjacency list for each node from user
		cout << "Enter adjacnecy list (comma-delimited) for node " << i << ": ";
		string rel;
		getline(cin, rel);
		stringstream relStream(rel);

		getline(relStream, rel, ',');
		Node* head = new Node(stoi(rel), nullptr);
		Node* curPtr = head;
		//while there are still values to parse populate linked list
		while (relStream.good())
		{
			getline(relStream, rel, ',');
			curPtr->next = new Node(stoi(rel), nullptr);
			curPtr = curPtr->next;
		}
		adjList[i] = head;
	}

	//get starting node
	cout << "Enter starting node: ";
	cin >> startNode;
	cin.ignore();

	//create Graph object and run DFS and BFS
	Graph* myGraph = new Graph(numNodes, adjList);
	cout << "\nDFS: ";
	myGraph->DFS(startNode);
	cout << endl;
	cout << "BFS: ";
	myGraph->BFS(startNode);
	cout << endl;

	//memory management
	for (size_t i = 0; i < 10; i++)
	{
		if (adjList[i] != nullptr)
		{
			Node* curNode = adjList[i];
			Node* prevNode = curNode;
			while (curNode->next != nullptr)
			{
				curNode = curNode->next;
				delete prevNode;
				prevNode = curNode;
			}
			delete curNode;
		}
	}

	system("PAUSE");
	return 0;
}

Graph::Graph(int argNumNodes, Node* argAdjList[])
{
	setNumNodes(argNumNodes);
	setAdjList(argAdjList);
}

void Graph::DFS_util(bool visited[], int u)
{
	visited[u] = true;	//set u to visited
	cout << u << " ";	//print u
	Node* curNode = getAdjList(u);	//get adj list for u and iterate through
	while (curNode != nullptr)
	{
		int v = curNode->val;
		if (!visited[v])
			DFS_util(visited, v);
		curNode = curNode->next;
	}
}

//perform depth first search on graph
void Graph::DFS(int startNode)
{
	bool visited[10];	//init visited array to false
	for (size_t i = 0; i < 10; i++)
		visited[i] = false;

	DFS_util(visited, startNode);
}

//perform breadth first search on graph
void Graph::BFS(int startNode)
{
	queue<int> toVisit;	//queue to keep track of visiting order
	bool visited[10];	//init visited array to false
	for (size_t i = 0; i < 10; i++)
		visited[i] = false;	

	toVisit.push(startNode);	//enqueue root
	visited[startNode] = true;	//set root to visited
	
	while (!toVisit.empty())
	{
		int u = toVisit.front();	//get front of queue and dequeue
		toVisit.pop();
		cout << u << " ";			//value gotten from queue

		Node* curNode = getAdjList(u);
		while (curNode != nullptr)	//iterate through adjacent nodes adding
		{					//adding them to the queue if they are undiscovered
			int v = curNode->val;
			if (!visited[v])
			{
				visited[v] = true;
				toVisit.push(v);
			}
			curNode = curNode->next;
		}
	}
}
