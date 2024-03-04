/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "apsp.h"
#include "graph.h"
#include "kattisio.h"

#include <limits>
#include <vector>

std::vector<std::vector<int>> calculate_pairwise_winners(const std::vector<Ballot> &ballots)
{
    int num_candidates = ballots[0].preferences.size();
    std::vector<std::vector<int>> points(num_candidates, std::vector<int>(num_candidates, 0));

    for (const Ballot &ballot : ballots)
    {
        for (int i = 0; i < num_candidates; i++)
        {
            for (int j = 0; j < num_candidates; j++)
            {
                if (i != j)
                {
                    // i has a higher priority in the ballot than j and thus gets all the votes
                    if (ballot.preferences[i] < ballot.preferences[j])
                    {
                        points[i][j] += ballot.num_votes;
                    }
                    else
                    {
                        points[j][i] += ballot.num_votes;
                    }
                }
            }
        }
    }

    return points;
}

std::vector<bool> solve_problem(const std::vector<Ballot> &ballots)
{
    int num_candidates = ballots[0].preferences.size();
    std::vector<bool> output;
    output.reserve(num_candidates);

    std::vector<std::vector<int>> points = calculate_pairwise_winners(ballots);

    AdjacencyListGraph g = AdjacencyListGraph(num_candidates);
    for (int i = 0; i < num_candidates; i++)
    {
        for (int j = 0; j < num_candidates; j++)
        {
            if (i != j)
            {
                // i has more votes than j
                if (points[i][j] > points[j][i])
                {
                    g.addEdge(i, j, 1, false);
                }
                else
                {
                    g.addEdge(j, i, 1, false);
                }
            }
        }
    }

    std::vector<std::vector<double>> distances = floydWarshall(g);

    for (int i = 0; i < num_candidates; i++)
    {
        // check if vertex i connects to all other vertices
        bool connects_to_all = true;

        for (int j = 0; j < num_candidates; j++)
        {
            if (distances[i][j] == std::numeric_limits<double>::max())
            {
                connects_to_all = false;
                break;
            }
        }

        output.push_back(connects_to_all);
    }

    return output;
}