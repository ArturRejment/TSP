#include<iostream>
using namespace std;

class Graph
{
	protected:
		int optimum;
		int vertices;
		int edges;
		int **matrix;

	public:
		Graph();
		~Graph();
		int getVertices();
		int **getMatrix();
		int getOptimumPath();

		void printMatrix();
		void importFromFile();
		void createMatrix(string);
		void addEdge(int, int, int);
		int getPathWeight(int, int);
};

