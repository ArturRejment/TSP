#include<iostream>
#include<vector>
#include"../Graph/graph.cpp"
#include"utils.cpp"

using namespace std;


int countCostOfPermutation(Graph *graph, vector<int> permutation, int numberOfVertices)
{
	int i;
	int costOfPermutation = 0;
	int permutationSize = permutation.size();

	costOfPermutation += graph->getPathWeight(0, permutation[0]);
	for (i = 0; i < numberOfVertices - 2; i++)
	{
		costOfPermutation += graph->getPathWeight(permutation[i], permutation[i + 1]);
	}
	costOfPermutation += graph->getPathWeight(permutation[permutationSize - 1], 0);

	return cost;
}


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


double findStartingTemperature(Graph *graph, int numberOfVertices)
{
	int i;
	int bestCost = 0, tempCost;
	int costOfStarting, costOfSwaped;

	// Vectors with initial permutation
	vector<int> startingPermutation, vector<int> swapedPermutation = findStartingPermutation(graph);

	startingPermutation = swapRandomElements(startingPermutation);
	for (i = 0; i < numberOfVertices; i++)
	{
		swapedPermutation = swapRandomElements(previousPermutation);
		costOfStarting = countCostOfPermutation(graph, startingPermutation, numberOfVertices);
		costOfSwaped = countCostOfPermutation(graph, previousPermutation, numberOfVertices);

		tempCost = abs(costOfStarting - costOfSwaped);
		if(tempCost > bestCost)
		{
			bestCost = tempCost;
		}
		startingPermutation = swapedPermutation;
	}

	return bestCost;
}


pair<vector<int>, int> simmulatedAnnealing(Graph *graph)
{
	random_device rd;
	mt19937 g(rd());

	int numberOfVertices = graph->getVertices();
	vector<int> permutation = findStartingPermutation(graph, numberOfVertices);
	vector<int> bestPermutation = permutation;

	int cost = countCostOfPermutation(graph, bestPermutation, numberOfVertices);
	int previousCost, bestCost = cost;

	double startingTemperature = findStartingTemperature(graph, numberOfVertices);
}