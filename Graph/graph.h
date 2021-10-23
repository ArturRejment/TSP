#include<iostream>
using namespace std;

class Graph
{
	protected:
		int vertices;
		int edges;
		int **matrix;

	public:
		Graph();
		~Graph();
		int getVertices();
		int getEdges();
		int **getMatrix();

		void printMatrix();
		void importFromFile();
		void createMatrix(string);
		void addEdge(int, int, int);
};

