/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------

*/

#include "dictHeap.h"
#include "graph.h"
#include "kattisio.h"

#include <limits>
#include <tuple>
#include <vector>

int solve_query(const Graph &g, const std::tuple<int, int, int> &query, const std::vector<int> &fuel_prices)
{
    int fuel_capacity = std::get<0>(query);
    int start_vertex = std::get<1>(query);
    int target_vertex = std::get<2>(query);

    std::vector<std::vector<int>> prices(g.getNumVertices(),
                                         std::vector<int>(fuel_capacity, std::numeric_limits<int>::max()));
    for (int i = 0; i < fuel_capacity; i++)
    {
        prices[start_vertex][i] = i * fuel_prices[start_vertex];
    }

    BinaryDictHeap<int> prioQ = BinaryDictHeap<int>(true);
    prioQ.insert(start_vertex, 0);
    std::vector<double> distance(g.getNumVertices(), std::numeric_limits<double>::infinity());
    distance[start_vertex] = 0;

    while (!prioQ.empty())
    {
        int cur = prioQ.extract();

        for (const std::pair<int, double> &neighbour : g.getNeighbours(cur))
        {
            for (int i = 0; i < fuel_capacity; i++)
            {
            }
        }
    }
}

std::vector<int> solve_problem(const Test_case &test_case)
{
    std::vector<int> output;

    AdjacencyListGraph g = AdjacencyListGraph(test_case.num_vertices);
    for (const std::tuple<int, int, int> &edge : test_case.edges)
    {
        g.addEdge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge), true);
    }

    return output;
}
