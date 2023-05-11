#include "graph.h"

#include <iostream>

int main()
{
    AdjacencyMatrixGraph g = AdjacencyMatrixGraph<3>();
    g.matrix = {true, false, true, false, true, false, false, true, true};

    std::vector<int> neighbours = g.getNeighbours(1);
    for (int i = 0; i < neighbours.size(); i++)
    {
        std::cout << neighbours[i] << "\n";
    }

    return 0;
}