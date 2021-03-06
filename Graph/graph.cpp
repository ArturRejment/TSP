#include<iostream>
#include<fstream>
#include<iomanip>
#include"graph.h"

using namespace std;

Graph::Graph()
{
	vertices = 0;
	optimum = 0;
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

int Graph::getOptimumPath()
{
	return optimum;
}

int **Graph::getMatrix()
{
	return matrix;
}

void Graph::printMatrix()
{
	int i, j;
	cout << "      |";
	for (i = 0; i < vertices; i++)
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
		return;
	}

	fstream file;
	file.open(fileName, ios::in);

	if (!file.is_open())
	{
		cout << "Could not open " << fileName;
		return;
	}

	file >> name;
	file >> this->vertices;
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
	file >> optimum;
	cout << "Graph filled correctly! :)" << endl;
	file.close();
}

int Graph::getPathWeight(int first, int second)
{
	return matrix[first][second];
}

bool Graph::isEmpty()
{
	if(matrix == nullptr)
		return true;
	return false;
}