#include<iostream>
#include<fstream>
#include<iomanip>
#include"graph.h"

using namespace std;

Graph::Graph()
{
	vertices = 0;
	edges = 0;
	matrix = nullptr;
}

Graph::~Graph()
{
	for (int i = 0; i < vertices; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int Graph::getVertices()
{
	return vertices;
}

int **Graph::getMatrix()
{
	return matrix;
}

int Graph::getEdges()
{
	return edges;
}

void Graph::printMatrix()
{
	int i, j;
	cout << "      |";
	for (i = 0; i < edges;i++)
		cout << setw(6) << i;
	cout << "\n   ---|";
    for (int i = 0; i < vertices * 6 + 2; i++)
        cout << "-" << flush;
    cout << "\n";
    for (i = 0; i < vertices; i++)
    {
        cout << setw(6) << i << "|";
        for (j = 0; j < vertices; j++)
            cout << setw(6) << matrix[i][j];
        cout << "\n";
    }
}

void Graph::createMatrix(string fileName)
{
	int i, j, value;
	string name;

	if(matrix != nullptr)
	{
		cout << "Graph is not empty!\n";
	}

	fstream file;
	file.open(fileName, ios::in);

	if (!file.is_open())
	{
		cout << "Could not open " << fileName;
	}

	file >> name;
	file >> vertices;
	matrix = new int *[vertices];
	for (int i = 0; i < vertices; i++)
		matrix[i] = new int[vertices];

	// Fill matrix from file
	for (i = 0; i < vertices; i++)
		for (j = 0; j < vertices;j++)
		{
			file >> value;
			matrix[i][j] = value;
		}
}

int Graph::getPathWeight(int first, int second)
{
	return matrix[first][second];
}