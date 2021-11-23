#include<vector>

// const int MAXVALUE = 2147483647; // Const represents infinity

using namespace std;

int heldKarp(Graph *graph)
{
    int numberOfVertices = graph->getVertices();
    int numberOfCombinations = 1<<numberOfVertices;

	vector<vector<int>> path(numberOfCombinations, vector<int>(numberOfVertices, MAXVALUE));

	for (int visited = 1; visited < numberOfCombinations; ++visited)
    {
        for (int last = 0; last < numberOfVertices - 1; ++last)
        {

            bool alreadyVisited = !(visited & 1<<last);
            if(alreadyVisited) continue;

            if(visited == 1<<last){

                path[visited][last] = graph->getPathWeight(numberOfVertices - 1, last);
            } else {
                int prev_visited = visited ^ 1<<last;
                for (int prev = 0; prev < numberOfVertices - 1; ++prev) {
                    if (!(prev_visited & 1<<prev)) continue;

                    int tempMin = graph->getPathWeight(last, prev) + path[prev_visited][prev];
                    if(tempMin < path[visited][last]){
                        path[visited][last] = tempMin;
                    }
                }
            }
        }
    }

    int answer = MAXVALUE;
    for(int last = 0; last < numberOfVertices - 1; ++last)
    {
        int tempMin = graph->getPathWeight(last, numberOfVertices - 1) + path[(1<<(numberOfVertices-1))-1][last];

        if(tempMin < answer){
            answer = tempMin;
        }
    }

    return answer;
}