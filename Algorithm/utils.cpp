#include<vector>
#include<ctime>
#include<cstdlib>
#include<numeric>
#include<iomanip>


void printFoundNewBest(int numberOfIterations, int bestCost, Graph *graph)
{
	double prd = double(100 * (bestCost - graph->getOptimumPath())) / graph->getOptimumPath();
	cout << numberOfIterations << ": " << bestCost << " (" << fixed << setprecision(4) << prd << "%)" << endl;
	return;
}


vector<int> swapRandomElements(vector<int> permutation)
{
	int permutationSize = permutation.size();
	int first = rand() % (permutationSize - 1);
	int second = rand() % (permutationSize - 1);

	if(first != second)
		iter_swap(permutation.begin() + first, permutation.begin() + second);

	return permutation;
}


vector<int> insertRandomElements(vector<int> permutation)
{
	int permutationSize = permutation.size();
	int first = rand() % (permutationSize - 1);
	int second = rand() % (permutationSize - 1);

	if(first > second)
	{
		swap(first, second);
	}

	vector<int>::iterator it;
	it = permutation.begin() + second;
	int insertingValue = *it;
	it = permutation.erase(it);
	permutation.insert(permutation.begin() + first, insertingValue);
	return permutation;
}