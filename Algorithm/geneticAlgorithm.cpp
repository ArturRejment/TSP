#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <windows.h>

const double crossoverProbability = 0.9;
const double mutationProbability = 0.05;
random_device rd;
mt19937 rng(rd());

int countCostOfPermutation(Graph *graph, vector<int> permutation)
{
    int i;
    int costOfPermutation = 0;
    int permutationSize = permutation.size();
    int numberOfVertices = graph->getVertices();

    costOfPermutation += graph->getPathWeight(0, permutation[0]);
    for (i = 0; i < numberOfVertices - 2; i++)
    {
        costOfPermutation += graph->getPathWeight(permutation[i], permutation[i + 1]);
    }
    costOfPermutation += graph->getPathWeight(permutation[permutationSize - 1], 0);

    return costOfPermutation;
}


vector<int> randomPermutation(int numberOfVertices)
{
    vector<int> randomPermutation(numberOfVertices - 1);
    iota(randomPermutation.begin(), randomPermutation.end(), 1);
    shuffle(randomPermutation.begin(), randomPermutation.end(), rng);
    return randomPermutation;
}


vector<int> selectParentsIndexes(vector<int> chromosomeGrades, int populationSize)
{
    /* Function returns vector with indexes of parents chosen to reproduce in next generation */

    int sumOfGrades = 0;
    vector<int> parentsIndexes(populationSize);
    // Sum all grades
    for (int i = 0; i < populationSize; i++)
    {
        sumOfGrades += chromosomeGrades[i];
        chromosomeGrades[i] = sumOfGrades;
    }

    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, sumOfGrades - 1);

    for (int i = 0; i < populationSize; i++)
    {
        int selected = distribution(rng);
        for (int j = 0; j < populationSize; j++)
            if(selected < chromosomeGrades[j])
            {
                parentsIndexes[i] = j;
                break;
            }
    }

    return parentsIndexes;
}


vector<vector<int>> reproducePopulation(vector<vector<int>> population, vector<int> parentsIndexes)
{
    /* Returns new, reproduced population based on old generation and best parents */

    vector<vector<int>> newPopulation;
    for (int i = 0; i < population.size(); i++)
        newPopulation.push_back(population[parentsIndexes[i]]);

    return newPopulation;
}


vector<int> gradeChromosomes(Graph *graph, vector<vector<int>> population, int populationSize, int bestChromosomeCost)
{
    int minimumGrade = 0, i, chromosomeCost;
    vector<int> grades;

    for (i = 0; i < populationSize; i++)
    {
        chromosomeCost = countCostOfPermutation(graph, population[i]);
        grades.push_back(bestChromosomeCost - chromosomeCost);
    }

    // Grades normalization
    // Find minimum, negative grade
    for (i = 0; i < populationSize; i++)
        if(grades[i] < minimumGrade)
            minimumGrade = grades[i];

    minimumGrade = (minimumGrade * (-1)) + 1;
    for (i = 0; i < populationSize; i++)
        grades[i] += minimumGrade;

    return grades;
}


int findInVector(vector<int> vector, int number)
{
    for (int i = 0; i < vector.size(); i++)
        if(vector[i] == number)
            return i;

    return -1;
}


vector<vector<int>> performCrossover(vector<vector<int>> permutation, std::uniform_real_distribution<double> probability, int numberOfVertices)
{
    /* Perform children crossovers */

    int range;
    vector<int> tempChromosomeA, tempChromosomeB;

    range = permutation.size() / 2;

    for (int i = 0; i < range; i++)
    {
        if (probability(rng) <= crossoverProbability)
        {
            tempChromosomeA = permutation[i * 2];
            tempChromosomeB = permutation[i * 2 + 1];

            // Random crossing point
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, (numberOfVertices - 1));
            int crossingPoint = dist(rng);

            // Cross chromosomes
            for (int j = 0; j < crossingPoint; j++)
            {
                int position = findInVector(permutation[i * 2], tempChromosomeB[j]);
                permutation[i * 2][position] = permutation[i * 2][j];
                permutation[i * 2][j] = tempChromosomeB[j];
            }
            for (int j = 0; j < crossingPoint; j++)
            {
                int position = findInVector(permutation[i * 2 + 1], tempChromosomeA[j]);
                permutation[i * 2 + 1][position] = permutation[i * 2 + 1][j];
                permutation[i * 2 + 1][j] = tempChromosomeA[j];
            }
        }
    }

    return permutation;
}

vector<int> permutationSwap(vector<int> permutation, int firstIndex, int secondIndex)
{
    if(firstIndex != secondIndex) iter_swap(permutation.begin() + firstIndex, permutation.begin() + secondIndex);

    return permutation;
}

vector<vector<int>> performMutations(vector<vector<int>>population, std::uniform_real_distribution<double> probability){
    for(int i = 0; i < population.size(); i++){
        if(probability(rng) <= mutationProbability){
            vector<int> tempPermutation = population[i];
            std::uniform_int_distribution<std::mt19937::result_type> popDist(0, tempPermutation.size() - 1);
            int pointA, pointB;
            do{
                pointA = popDist(rng);
                pointB = popDist(rng);
            } while (pointA == pointB);

            tempPermutation = permutationSwap(tempPermutation, pointA, pointB);
            population[i] = tempPermutation;
        }
    }
    return population;
}

pair<vector<int>, int> geneticAlgorithm(Graph *graph)
{
    //
    const int populationSize = 500;
    const int numberOfGenerations = 15000;
    //

    int numberOfVertices = graph->getVertices();
    vector<int> selectedParentsIndexes;

    vector<int> bestChromosome = findStartingPermutation(graph, numberOfVertices);
    int bestChromosomeCost = countCostOfPermutation(graph, bestChromosome);

    vector<vector<int>> population;
    population.push_back(bestChromosome);
    for (int i = 1; i < populationSize; i++)
        population.push_back(randomPermutation(numberOfVertices));

    vector<vector<int>> newPopulation;
    vector<int> chromosomesGrades = gradeChromosomes(graph, population, populationSize, bestChromosomeCost);

    std::uniform_real_distribution<double> probability(0.0, 1.0);

    int bestGrade = -99999999;
    int bestFromPopulation = 0;

    for (int i = 0; i < numberOfGenerations; i++)
    {
        selectedParentsIndexes = selectParentsIndexes(chromosomesGrades, population.size());
        newPopulation = reproducePopulation(population, selectedParentsIndexes);

        newPopulation = performCrossover(newPopulation, probability, numberOfVertices);
        newPopulation = performMutations(newPopulation, probability);

        chromosomesGrades = gradeChromosomes(graph, newPopulation, populationSize, bestChromosomeCost);

        population = newPopulation;

        for (int j = 0; j < populationSize; j++)
        {
            if (chromosomesGrades[j] > bestGrade)
            {
                bestGrade = chromosomesGrades[j];
                bestFromPopulation = j;
            }
        }
        if (countCostOfPermutation(graph, population[bestFromPopulation]) < bestChromosomeCost)
        {
            bestChromosome = population[bestFromPopulation];
            bestChromosomeCost = countCostOfPermutation(graph, bestChromosome);
            printFoundNewBest(i, bestChromosomeCost, graph);
        }
    }

    return make_pair(bestChromosome, bestChromosomeCost);
}
