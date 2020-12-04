#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class Node
{
private:
	int node;
	int weight;
	Node* next = nullptr;
	void setNode(int arg) { node = arg; }
public:
	void setWeight(int arg) { weight = arg; }
	void setNext(Node* arg) { next = arg; }
	int getNode() { return node; }
	int getWeight() { return weight; }
	Node* getNext() { return next; }

	Node(int argNode, int argWeight)
	{
		setNode(argNode);
		setWeight(argWeight);
	}
};

class Graph
{
private:
	int size;
	void setSize(int argSize) { size = argSize; }
public:
	Node** matrix;
	int getSize() { return size; }

	void addEdge(int u, int v, int weight)
	{	//add edge to adj graph
		if (matrix[u] == nullptr)
		{
			matrix[u] = new Node(v, weight);
			return;
		}
		Node* cur = matrix[u];
		while (cur->getNext() != nullptr)
			cur = cur->getNext();
		cur->setNext(new Node(v, weight));
	}

	int getEdgeWeight(int u, int v)
	{	//get weight from edge u to v
		Node* cur = matrix[u];
		while (cur != nullptr && cur->getNode() != v)
			cur = cur->getNext();
		if (cur == nullptr)
			return -1;
		return cur->getWeight();
	}

	void print()
	{	//display graph
		for (size_t i = 0; i < getSize(); i++)
		{
			Node* cur = matrix[i];
			cout << i << ": ";
			while (cur != nullptr)
			{
				cout << cur->getNode() << "," << cur->getWeight() << " -> ";
				cur = cur->getNext();
			}
			cout << endl;
		}
	}

	Graph(int argSize)
	{
		setSize(argSize);
		matrix = new Node* [getSize()];
		for (size_t i = 0; i < getSize(); i++)
			matrix[i] = nullptr;
	}
	void cleanup()
	{
		for (size_t i = 0; i < getSize(); i++)
		{
			Node* cur = matrix[i];
			Node* next = cur;
			while (cur != nullptr)
			{
				next = cur->getNext();
				delete cur;
				cur = next;
			}
		}
		delete[] matrix;
	}
};

class minPQ
{
private:
	vector<Node> q;
public:
	Node top()
	{	//get top value from queue
		return q.front();
	}
	void pop()
	{	//remove top value from queue
		q.erase(q.begin());
	}
	void push(Node myNode)
	{
		//push new value to back of queue and sort into queue
		q.push_back(myNode);
		int cur = q.size() - 1;
		while (cur > 0 && q[cur].getWeight() < q[cur - 1].getWeight())
		{
			swap(q[cur], q[cur - 1]);
			cur--;
		}
	}
	bool decKey(int key, int newWeight)
	{
		int index = find(key);	//find key in queue
		if (index == -1)		//if not in queue return false
		{
			cout << "ERROR:Not in queue\n";
			return false;
		}
		if (newWeight > q[index].getWeight())	//if new weight too large
		{										//return false
			cout << "ERROR:New weight larger than old weight\n";
			return false;
		}
		q[index].setWeight(newWeight);
		while (index > 0 && q[index].getWeight() < q[index - 1].getWeight())
		{
			swap(q[index], q[index - 1]);
			index--;
		}
		return true;
	}
	bool empty()
	{
		return !q.size();
	}
	int find(int key)
	{
		//iterate through queue looking for value
			//return the index if found
			//return -1 if not found
		for (size_t i = 0; i < q.size(); i++)
		{
			if (q[key].getNode() == key)
				return i;
		}
		return -1;
	}
};

//function prototypes
void dijkstra(Graph G, int start);

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
	Graph myGraph(size);
	string input;
	getline(cin, input);
	stringstream inputs(input);
	while (inputs.good())
	{
		string u;
		string v;
		string weight;
		getline(inputs, u, ',');
		getline(inputs, v, ',');
		getline(inputs, weight, ';');

		myGraph.addEdge(stoi(u), stoi(v), stoi(weight));
	}
	myGraph.print();

	cout << endl;
	dijkstra(myGraph, start);
}

void dijkstra(Graph G, int start)
{
	int* estArr = new int[G.getSize()];
	//init array to inf
	for (size_t i = 0; i < G.getSize(); i++)
		estArr[i] = INT_MAX;
	
	//set starting point
	estArr[start] = 0;

	minPQ pq;
	for (size_t i = 0; i < G.getSize(); i++)
		pq.push(Node(i, estArr[i]));

	//shortest path set
	vector<Node> S;
	while (!pq.empty())
	{
		//extract min
		Node u = pq.top();
		pq.pop();
		
		//add u to shortest path set S
		S.push_back(u);

		Node* v = G.matrix[u.getNode()];	//get adj matrix of u
		while (v != nullptr)
		{
			int newWeight = estArr[u.getNode()] +
				G.getEdgeWeight(u.getNode(), v->getNode());
			if (estArr[v->getNode()] > newWeight);
			{
				estArr[v->getNode()] = newWeight;
				pq.decKey(v->getNode(), newWeight);
			}
			v = v->getNext();
		}
	}
	
	cout << "Source\t\t" << "Distance from root";
	for (size_t i = 0; i < G.getSize(); i++)
	{
		cout << i << "\t\t" << estArr[i];
	}

	delete[] estArr;
}