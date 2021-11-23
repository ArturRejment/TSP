#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

const int MAXVALUE = 2147483647; // Const represents infinity

using namespace std;

double calculatePRD(int length, int optimum)
{
    return double(100 * (length-optimum)/optimum);
}

vector<int> brute_force(Graph graph)
{
	int starting_vertex = 0;
	int number_of_nodes = graph.getVertices();
	int **matrix = graph.getMatrix();

	vector<int> all_nodes;
	for (int i = 1; i < number_of_nodes; i++)
	{
		all_nodes.push_back(i);
	}

	int size = all_nodes.size();

	vector<int> result;
	int TSP_shortest_path = MAXVALUE;
	do
    {
        int path_weight = 0;
        int j = starting_vertex;
        for (int i = 0; i < size; i++)
        {
            path_weight += matrix[j][all_nodes[i]];
            j = all_nodes[i];
        }
        path_weight += matrix[j][starting_vertex];

        // Found new shortest path
        if (path_weight < TSP_shortest_path)
        {
            TSP_shortest_path = path_weight;
            result.clear();
            result.push_back(starting_vertex);
            for (int i = 0; i < size; i++)
            {
                result.push_back(all_nodes[i]);
            }

            cout << "New Best Path Found! " << TSP_shortest_path << "    PRD: " << calculatePRD(TSP_shortest_path, graph.getOptimumPath()) << " %\n";
        }
    } while (next_permutation(all_nodes.begin(), all_nodes.end()));
    result.push_back(starting_vertex);
    result.push_back(TSP_shortest_path);

    all_nodes.clear();

    return result;
}