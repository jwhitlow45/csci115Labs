#include<iostream>
#include<queue>
#include<string>
#include<sstream>
using namespace std;

class Node
{
private:
	int node;									//node edge is connecting to
	int weight;									//weight of edge
	int parent;									//parent of node
	Node* next;									//next edge in adj matrix
	void setNode(int arg) { node = arg; }		//set node connection
public:
	void setNext(Node* arg) { next = arg; }		//set next edge
	void setParent(int arg) { parent = arg; }	//set parent of node
	void setWeight(int arg) { weight = arg; }	//set weight of edge
	int getNode() { return node; }				//get node connection
	int getWeight() { return weight; }			//get weight
	Node* getNext() { return next; }			//get next node in linked list

	//constructors
	Node(int argNode, int argWeight)
	{
		setNode(argNode);
		setWeight(argWeight);
		setNext(nullptr);
	}
	Node(int argNode, int argWeight, Node* argNext)
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
	Node** adjMatrix;
	void setSize(int arg) { size = arg; }
	void setAdjMatrix(Node** arg) { adjMatrix = arg; }
	bool compNodes(Node* a, Node* b)	//compare function for priority queue
	{
		return (a->getWeight() < b->getWeight());
	}
public:
	int getSize() { return size; }

	//find minimum spanning tree using prim algorithm
	void primMST(int startNode)
	{
		//comparitor function for priority queue
		auto compareNode = [](Node left, Node right)
		{
			return (left.getWeight() > right.getWeight());
		};
		priority_queue<Node, vector<Node>,	//priority queue for prim
			decltype(compareNode)> nodePQ(compareNode);
		
		for (size_t i = 0; i < size; i++)
		{
			Node myNode = *adjMatrix[i];
			myNode.setWeight(int(INFINITY));
			myNode.setParent(NULL);
			nodePQ.push(myNode);
		}
	}

	//find minimum spanning tree using kruskal algorithm
	void kruskalMST()
	{

	}


	//print graph adjacency matrix
	void print()
	{
		cout << '\t';	//print column labels
		for (size_t i = 0; i < size; i++)
			cout << i << '\t';
		cout << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << i << '\t';			//print row labels
			Node* cur = adjMatrix[i];	//set cur to first element of
											//linked list
			int j = 0;					//keep track of which column is being
											//printed to
			while (cur != nullptr)	
			{	//print nodes until end of linked list
				while (cur->getNode() > j)
				{						//print as empty until a column with
											//content is reached
					cout << "inf\t";
					j++;				//iterate to next column
				}
				cout << cur->getWeight() << '\t';	//print weight
				cur = cur->getNext();				//iterate to next node
				j++;								//iterate to next column
			}
			while (j < size)
			{	//print for remaining columns after end of linked list
				cout << "inf\t";
				j++;
			}
			cout << endl;			
		}
	}

	//constructor and destructor
	Graph(int argSize, Node** argAdjMatrix)
	{
		setSize(argSize);
		setAdjMatrix(argAdjMatrix);
	}
	~Graph()
	{
		for (size_t i = 0; i < size; i++)
		{
			Node* cur = adjMatrix[i];
			Node* next = cur;
			while (cur != nullptr)
			{
				next = next->getNext();
				delete cur;
				cur = next;
			}
		}
		delete[] adjMatrix;
	};
};

//function prototypes
Node* buildAdjRow(string);	//builds adjacency row given string in format
								//node;weight,node;weight,...,node;weight

int main()
{
	string strSize;
	//get size of graph from user
	cout << "Enter size of graph: ";
	getline(cin, strSize);
	int size = stoi(strSize);
	Node** adjMatrix = new Node*[size];
	
	//get adj matrix from user line by line
	cout << "***Enter edges in asencding order by node number***\n";
	for (size_t i = 0; i < size; i++)
	{
		cout << "Enter weights for node " << i << " (node;weight,node;weight,...): ";
		string userRow;
		getline(cin, userRow);
		adjMatrix[i] = buildAdjRow(userRow);
	}

	Graph myGraph(size, adjMatrix);
	myGraph.print();
	myGraph.primMST();

	return 0;
}

Node* buildAdjRow(string row)
{
	if (row == "")
		return nullptr;
	Node* HEAD = new Node(0, 0);
	Node* cur = HEAD;
	stringstream ssRelations(row);
	while (ssRelations.good())
	{
		//traverse the string properties building the adjacency matrix
		string node;
		string weight;
		string props;
		getline(ssRelations, props, ',');
		stringstream ssProps(props);
		getline(ssProps, node, ';');
		getline(ssProps, weight, ';');
		cur->setNext(new Node(stoi(node), stoi(weight)));
		cur = cur->getNext();
	}
	cur = HEAD->getNext();
	delete HEAD;
	return cur;
}
