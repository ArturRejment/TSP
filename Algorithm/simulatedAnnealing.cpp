#include<iostream>
#include<vector>
#include"../Graph/graph.cpp"

using namespace std;


vector<int> findStartingPermutation(Graph *graph, int numberOfVertices)
{
	int inner, outer, i;
	int previousVertex, minimumVertex, minimalCost, tempVertex;
	vector<int> startingPermutation;
	vector<int> availableVertices(numberOfVertices - 1);
	// Fill vector with availabe vertices with numbers starting from 1 to numberOfVertices-1
	iota(availableVertices.begin(), availableVertices.end(), 1);

	for (outer = 0; outer < numberOfVertices - 1; outer++)
	{
		minimumVertex = 0;
		minimalCost = 9999999;
		for (inner = 0; inner < availableVertices.size(); inner++)
		{
			tempVertex = availableVertices[inner];
			if(graph->getPathWeight(previousVertex, tempVertex) < minimalCost && previousVertex != tempVertex)
			{
				minimumVertex = tempVertex;
				minimalCost = graph->getPathWeight(previousVertex, minimumVertex);
			}
		}
		// Append vertex with minimum path to the starting permutation's vector
		startingPermutation.push_back(minimumVertex);

		// Erase appended minimum vertex from vector with still available vertices
		for (i = 0; i < availableVertices.size() - 1; i++)
		{
			if(availableVertices[i] == minimumVertex)
			{
				availableVertices.erase(availableVertices.begin() + i);
			}
		}
		previousVertex = minimumVertex;
	}

	return startingPermutation;
}


double findStartingTemperature(Graph *graph)
{
	// Vectors with initial permutation
	vector<int> startingPermutation, vector<int> previousPermutation = findStartingPermutation(graph);
}


pair<vector<int>, int> simmulatedAnnealing(Graph *graph)
{

}