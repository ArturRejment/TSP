#include<iostream>
using namespace std;

class Graph
{
	protected:
		int optimum;
		int vertices;
		int **matrix;

	public:
		Graph();
		~Graph();
		int getVertices();
		int **getMatrix();
		int getOptimumPath();
		bool isEmpty();

		void printMatrix();
		void importFromFile();
		void createMatrix(string);
		int getPathWeight(int, int);
};

