#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &string, const char &delimiter)
{
    std::vector<std::string> output;
    output.emplace_back("");
    int index = 0;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == delimiter)
        {
            index++;
            output.emplace_back("");
        }
        else
        {
            output[index] += string[i];
        }
    }
    return output;
}

std::vector<std::string> read_input()
{
    std::vector<std::string> output;
    std::string line;
    std::getline(std::cin, line);
    output.push_back(line);
    int height = std::stoi(split(line, ' ')[0]);

    for (int i = 0; i < height; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    std::getline(std::cin, line);
    output.push_back(line);
    int num_queries = std::stoi(line);

    for (int i = 0; i < num_queries; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<std::string>, std::vector<std::string>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> grid;
    std::vector<std::string> queries;
    std::vector<std::string> split_string = split(input[0], ' ');
    int height_grid = std::stoi(split_string[0]);
    grid.reserve(height_grid);

    for (int i = 1; i < height_grid + 1; i++)
    {
        grid.push_back(input[i]);
    }

    queries.reserve(input.size() - height_grid - 2);
    for (int i = height_grid + 2; i < input.size(); i++)
    {
        queries.push_back(input[i]);
    }

    return {grid, queries};
}

#endif