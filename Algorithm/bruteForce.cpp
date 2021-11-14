#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> brute_force(Graph graph)
{
	int starting_vertex = 0;
	vector<int> all_nodes;
	int number_of_nodes = graph.getVertices();
	int **matrix = graph.getMatrix();

	for (int i = 1; i < number_of_nodes; i++)
	{
		all_nodes.push_back(i);
	}
	int size = all_nodes.size();
	vector<int> result;
	int TSP_shortest_path = 9999999;
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
        if (path_weight < TSP_shortest_path)
        {
            TSP_shortest_path = path_weight;
            result.clear();
            result.push_back(starting_vertex);
            for (int i = 0; i < size; i++)
            {
                result.push_back(all_nodes[i]);
            }
        }
    } while (next_permutation(all_nodes.begin(), all_nodes.end()));
    result.push_back(starting_vertex);
    result.push_back(TSP_shortest_path);
    return result;
}