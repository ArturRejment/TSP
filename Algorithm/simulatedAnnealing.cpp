#include<iostream>
#include<vector>
#include<cmath>
#include<random>
#include<numeric>
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

	return costOfPermutation;
}


vector<int> findStartingPermutation(Graph *graph, int numberOfVertices)
{
	int inner, outer, i;
	int previousVertex, minimumVertex, minimalCost, tempVertex;
	vector<int> startingPermutation;
	vector<int> availableVertices(numberOfVertices - 1);
	// Fill vector with availabe vertices with numbers starting from 1 to numberOfVertices-1
	iota(availableVertices.begin(), availableVertices.end(), 1);

	previousVertex = 0;
	for (outer = 0; outer < numberOfVertices - 1; outer++)
	{
		minimumVertex = 0;
		minimalCost = 99999999;
		for (inner = 0; inner < availableVertices.size(); inner++)
		{
			tempVertex = availableVertices[inner];
			if (graph->getPathWeight(previousVertex, tempVertex) < minimalCost && previousVertex != tempVertex)
			{
				minimalCost = graph->getPathWeight(previousVertex, tempVertex);
				minimumVertex = tempVertex;
			}
		}
		// Append vertex with minimum path to the starting permutation's vector
		startingPermutation.push_back(minimumVertex);

		// Erase appended minimum vertex from vector with still available vertices
		vector<int>::iterator it = availableVertices.begin();
		while (it != availableVertices.end())
		{
			if ((*it) == minimumVertex)
			{
				it = availableVertices.erase(it);
			}
			else
			{
				it++;
			}
		}
		previousVertex = minimumVertex;
	}

	return startingPermutation;
}


double findStartingTemperature(Graph *graph, int numberOfVertices, mt19937 g)
{
	int i;
	int bestCost = 0, tempCost;
	int costOfStarting, costOfSwaped;

	// Vectors with initial permutation
	vector<int> startingPermutation = findStartingPermutation(graph, numberOfVertices);
	vector<int> swapedPermutation = startingPermutation;

	shuffle(swapedPermutation.begin(), swapedPermutation.end(), g);
	for (i = 0; i < numberOfVertices; i++)
	{
		shuffle(startingPermutation.begin(), startingPermutation.end(), g);
		costOfStarting = countCostOfPermutation(graph, startingPermutation, numberOfVertices);
		costOfSwaped = countCostOfPermutation(graph, swapedPermutation, numberOfVertices);

		tempCost = abs(costOfSwaped - costOfStarting);
		if(tempCost > bestCost)
		{
			bestCost = tempCost;
		}
		swapedPermutation = startingPermutation;
	}
	return bestCost;
}


pair<vector<int>, int> simmulatedAnnealing(Graph *graph)
{
	random_device rd;
	mt19937 g(rd());
	srand(time(NULL));

	int i;
	int numberOfVertices = graph->getVertices();
	int numberOfIterations;
	int numberOfSameCostIterations;
	vector<int> permutation = findStartingPermutation(graph, numberOfVertices);
	vector<int> bestPermutation = permutation;
	vector<int> newPermutation = permutation;

	int cost = countCostOfPermutation(graph, bestPermutation, numberOfVertices);
	int previousCost = cost; // for count nuber of same iterations
	int bestCost = cost;  // Best of all time
	int previousBestCost = 999999;  // Only for display newBestFound
	int newCost = cost;  // New cost of new permutation
	int era = 10 * numberOfVertices;
	double alpha = 0.9999;

	double startingTemperature = findStartingTemperature(graph, numberOfVertices, g);
	double currentTemperature = startingTemperature;

	cout << "Starting temperature: " << startingTemperature << endl;

	numberOfIterations = 0;
	numberOfSameCostIterations = 0;

	while(numberOfSameCostIterations < 1000 && currentTemperature > 0.00001)
	{
		if(previousCost == cost)
			numberOfSameCostIterations += 1;
		else
			numberOfSameCostIterations = 0;

		previousCost = cost;

		if (previousBestCost != bestCost)
			printFoundNewBest(numberOfIterations, bestCost, graph);

		for (i = 0; i < era; i++)
		{
			newPermutation = swapRandomElements(permutation);
			newCost = countCostOfPermutation(graph, newPermutation, numberOfVertices);

			if(newCost < cost)
			{
				permutation = newPermutation;
				cost = newCost;
			}
			else
			{
				uniform_real_distribution<> dis(0, 1);
				float s = dis(g);
				if(s < exp(-1 * (newCost - cost) / currentTemperature))
				{
					permutation = newPermutation;
					cost = newCost;
				}
			}
		}
		currentTemperature = startingTemperature * pow(alpha, ++numberOfIterations);
		previousBestCost = bestCost;
		if (cost < bestCost)
		{
			bestCost = cost;
			bestPermutation = permutation;
		}
	}
	bestPermutation.insert(bestPermutation.begin(), 0);
	bestPermutation.push_back(0);
	return make_pair(bestPermutation, bestCost);
}