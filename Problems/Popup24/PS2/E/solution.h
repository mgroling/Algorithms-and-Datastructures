#include "graph.h"
#include "prim_mst.h"

#include <string>
#include <vector>

std::pair<int, std::vector<std::pair<int, int>>> solve_problem(std::vector<std::string> dna_strings)
{
    int dna_string_length = dna_strings[0].size();
    AdjacencyListGraph g = AdjacencyListGraph(dna_strings.size());

    for (int i = 0; i < dna_strings.size(); i++)
    {
        for (int j = i + 1; j < dna_strings.size(); j++)
        {
            int distance = 0;
            for (int k = 0; k < dna_string_length; k++)
            {
                if (dna_strings[i][k] != dna_strings[j][k])
                {
                    distance++;
                }
            }
            g.addEdge(i, j, distance, true);
        }
    }

    std::tuple<std::vector<std::tuple<int, int>>, double> temp = primsAlgorithm(g);

    std::pair<int, std::vector<std::pair<int, int>>> output{std::get<1>(temp), std::vector<std::pair<int, int>>{}};
    for (const std::tuple<int, int> &edge : std::get<0>(temp))
    {
        output.second.push_back(std::pair<int, int>{std::get<0>(edge), std::get<1>(edge)});
    }

    return output;
}