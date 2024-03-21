/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "substring_search.h"

#include <queue>
#include <string>
#include <vector>

int grid_pos_to_int(const int &row, const int &col, const int &num_rows)
{
    return col * num_rows + row;
}

std::string create_permutations_recursive(const std::vector<std::string> &grid, const std::string &word, const int &row,
                                          const int &col, std::vector<bool> &visited, const int &max_length)
{
    if (word.size() == max_length)
    {
        return word + " ";
    }

    std::string output = "";
    visited[grid_pos_to_int(row, col, grid.size())] = true;

    if (row - 1 >= 0 && !visited[grid_pos_to_int(row - 1, col, grid.size())])
    {
        std::vector<bool> copy_visited = visited;
        output +=
            create_permutations_recursive(grid, word + grid[row - 1][col], row - 1, col, copy_visited, max_length);
    }

    if (row + 1 < grid.size() && !visited[grid_pos_to_int(row + 1, col, grid.size())])
    {
        std::vector<bool> copy_visited = visited;
        output +=
            create_permutations_recursive(grid, word + grid[row + 1][col], row + 1, col, copy_visited, max_length);
    }

    if (col - 1 >= 0 && !visited[grid_pos_to_int(row, col - 1, grid.size())])
    {
        std::vector<bool> copy_visited = visited;
        output +=
            create_permutations_recursive(grid, word + grid[row][col - 1], row, col - 1, copy_visited, max_length);
    }

    if (col + 1 < grid[0].size() && !visited[grid_pos_to_int(row, col + 1, grid.size())])
    {
        std::vector<bool> copy_visited = visited;
        output +=
            create_permutations_recursive(grid, word + grid[row][col + 1], row, col + 1, copy_visited, max_length);
    }

    return output;
}

std::string create_permutations(const std::vector<std::string> &grid, const int &max_length)
{
    std::string output = "";

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            std::string word;
            word.push_back(grid[i][j]);
            std::vector<bool> visited(grid.size() * grid[i].size(), false);
            output += create_permutations_recursive(grid, word, i, j, visited, max_length);
        }
    }

    return output;
}

int solve_problem(const std::pair<std::vector<std::string>, std::vector<std::string>> &problem)
{
    int max_length = 0;
    for (const std::string &elem : problem.second)
    {
        if (elem.size() > max_length)
        {
            max_length = elem.size();
        }
    }

    std::string text = create_permutations(problem.first, max_length);
    std::vector<std::vector<int>> occurences = substring_search(text, problem.second);
    int num_words_present = 0;

    for (int i = 0; i < occurences.size(); i++)
    {
        auto pos = problem.second[i].find(' ') == std::string::npos;
        if (occurences[i].size() && problem.second[i].find(' ') == std::string::npos)
        {
            num_words_present++;
        }
    }

    return num_words_present;
}