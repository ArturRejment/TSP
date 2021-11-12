#include<vector>
#include"../Graph/graph.h"

using namespace std;

int heldKarp(Graph *graph)
{
    int numberOfVertices = graph->getNumOfVertexes();
    int numberOfCombinations = 1<<numOfVer;

	vector<vector<int>> path(numberOfCombinations, vector<int>(numberOfVertices, INT_MAX));

	for (int visited = 1; visited < numberOfCombinations; ++visited)
    {
        for (int last = 0; last < numberOfVertices - 1; ++last)
        {
            int shift = 1<<last;
            // if last visited or path to itself
            bool alreadyVisited = !(visited & shift);
            if(alreadyVisited) continue;

            //try all possibilities, choose the paths among them
            if(visited == shift){
                //previous vertex must have been numOfVer-1
                path[visited][last] = graph->findElement(numberOfVertices - 1, last);
            } else {
                //previous vertex must have been one of the other
                int prev_visited = visited ^ shift;
                for (int prev = 0; prev < numberOfVertices - 1; ++prev) {
                    if (!(prev_visited & 1<<prev)) continue;

                    int tempMin = graph->findElement(last, prev) + path[prev_visited][prev];
                    if(tempMin < path[visited][last]){
                        path[visited][last] = tempMin;
                    }
                }
            }
        }
    }


    // use the path lengths to choose the cheapest cycle
    int answer = INT_MAX;
    for(int last = 0; last < numberOfVertices - 1; ++last)
    {
        int tempMin = graph->findElement(last, numberOfVertices - 1) + path[(1<<(numberOfVertices-1))-1][last];

        if(tempMin < answer){
            answer = tempMin;
        }
    }

    return answer;
}