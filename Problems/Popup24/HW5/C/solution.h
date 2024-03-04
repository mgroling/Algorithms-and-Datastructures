/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "graph.h"
#include "kattisio.h"
#include "prim_mst.h"

#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

int position_to_int(int row, int col, int num_rows)
{
    return row + col * num_rows;
}

std::vector<double> breadth_first_search(Graph &g, int start_vertex)
{
    // assumes that all distances are uniform (only counts path length)
    std::queue<int> vertex_queue;
    vertex_queue.push(start_vertex);
    std::vector<double> distances(g.getNumVertices(), std::numeric_limits<double>::max());
    distances[start_vertex] = 0;

    while (!vertex_queue.empty())
    {
        int cur_vertex = vertex_queue.front();
        double distance_cur = distances[cur_vertex];
        vertex_queue.pop();

        for (const std::tuple<int, double> &neighbour : g.getNeighbours(cur_vertex))
        {
            int neighbour_id = std::get<0>(neighbour);
            // neighbour has not been explored yet
            if (distances[neighbour_id] == std::numeric_limits<double>::max())
            {
                distances[neighbour_id] = distance_cur + 1;
                vertex_queue.push(neighbour_id);
            }
        }
    }

    return distances;
}

int solve_test_case(Test_case &test_case)
{
    std::unordered_map<int, int> map_position_to_id;
    int id = 0;
    for (int i = 0; i < test_case.num_rows; i++)
    {
        for (int j = 0; j < test_case.num_cols; j++)
        {
            if (test_case.maze[i][j] != '#')
            {
                map_position_to_id[position_to_int(i, j, test_case.num_rows)] = id;
                id++;
            }
        }
    }

    // translate the maze into a graph
    AdjacencyListGraph g = AdjacencyListGraph(id);
    for (int i = 0; i < test_case.num_rows; i++)
    {
        for (int j = 0; j < test_case.num_cols; j++)
        {
            if (test_case.maze[i][j] != '#')
            {
                // up
                if (i - 1 > 0 && test_case.maze[i - 1][j] != '#')
                {
                    g.addEdge(map_position_to_id[position_to_int(i, j, test_case.num_rows)],
                              map_position_to_id[position_to_int(i - 1, j, test_case.num_rows)], 1, false);
                }
                // down
                if (i + 1 < test_case.num_rows && test_case.maze[i + 1][j] != '#')
                {
                    g.addEdge(map_position_to_id[position_to_int(i, j, test_case.num_rows)],
                              map_position_to_id[position_to_int(i + 1, j, test_case.num_rows)], 1, false);
                }
                // left
                if (j - 1 > 0 && test_case.maze[i][j - 1] != '#')
                {
                    g.addEdge(map_position_to_id[position_to_int(i, j, test_case.num_rows)],
                              map_position_to_id[position_to_int(i, j - 1, test_case.num_rows)], 1, false);
                }
                // right
                if (j + 1 < test_case.num_cols && test_case.maze[i][j + 1] != '#')
                {
                    g.addEdge(map_position_to_id[position_to_int(i, j, test_case.num_rows)],
                              map_position_to_id[position_to_int(i, j + 1, test_case.num_rows)], 1, false);
                }
            }
        }
    }

    // calculate the indices of all vertices that are either the start position or an alien
    std::vector<int> important_vertices;
    important_vertices.reserve(test_case.alien_positions.size() + 1);
    important_vertices.push_back(map_position_to_id[position_to_int(test_case.start_position.row,
                                                                    test_case.start_position.col, test_case.num_rows)]);
    for (const Position &pos : test_case.alien_positions)
    {
        important_vertices.push_back(map_position_to_id[position_to_int(pos.row, pos.col, test_case.num_rows)]);
    }

    AdjacencyListGraph g_prime = AdjacencyListGraph(important_vertices.size());
    for (int i = 0; i < important_vertices.size(); i++)
    {
        int vertex = important_vertices[i];
        std::vector<double> distances = breadth_first_search(g, vertex);
        for (int j = 0; j < important_vertices.size(); j++)
        {
            if (i != j)
            {
                int other = important_vertices[j];
                g_prime.addEdge(i, j, distances[other], false);
            }
        }
    }

    return (int)std::get<1>(primsAlgorithm(g_prime));
}

std::vector<int> solve_problem(std::vector<Test_case> &test_cases)
{
    std::vector<int> output;
    output.reserve(test_cases.size());

    for (Test_case test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}