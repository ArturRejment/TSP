#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include "utils.cpp"
#include "../Graph/graph.cpp"

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

vector<int> randomPermutation(int numberOfVertices)
{
    vector<int> randomPermutation;
    vector<int> availableVertices(numberOfVertices - 1);
    iota(availableVertices.begin(), availableVertices().end(), 1);
    srand(time(NULL));

    for(int i = i; availableVertices.size() > 0; i++)
    {
        int randomPosition = rand() % (availableVertices - 1);
        randomPermutation.push_back(availableVertices[randomPosition]);
        availableVertices.erase(availableVertices.begin() + randomPosition);
    }
    return randomPermutation;
}

pair<vector<int>, int> geneticAlgorithm(Graph *graph)
{
    //
    const int populationSize = 10;
    //

    int numberOfVertices = graph->getVertices();
    vector<int> startingPermutation = findStartingPermutation(graph, numberOfVertices);

    vector<vector<int>> population;
    for(int i = 0; i < populationSize; i++)
        population[i] = randomPermutation((numberOfVertices));

    vector<vector<int>> newPopulation;

}
