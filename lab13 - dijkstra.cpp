#include<iostream>
#include<vector>

using namespace std;

class Graph
{
private:
	int** matrix;
	int size;
	void setSize(int argSize) { size = argSize; }
public:
	int getSize() { return size; }

	Graph(int argSize)
	{
		setSize(argSize);
		matrix = new int* [getSize()];
		for (size_t i = 0; i < getSize(); i++)
			matrix[i] = new int[3];
	}
	void cleanup()
	{
		for (size_t i = 0; i < getSize(); i++)
			delete[] matrix[i];
		delete[] matrix;
	}
};

int main()
{

	Graph myGraph(0);


	myGraph.cleanup();
}

void dijkstra(Graph G, int start)
{
	int*
}