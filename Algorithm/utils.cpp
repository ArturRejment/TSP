#include<vector>
#include<ctime>
#include<cstdlib>
#include<numeric>

vector<int> swapRandomElements(vector<int> permutation)
{
	srand(time(NULL));
	int permutationSize = permutation.size();
	int first = rand() % (permutationSize + 1);
	int second = rand() % (permutationSize + 1);

	iter_swap(permutation.begin() + first, permutation.begin() + second);

	return permutation;
}