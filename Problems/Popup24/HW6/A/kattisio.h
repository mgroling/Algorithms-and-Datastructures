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
    int num_edges = std::stoi(split(line, ' ')[1]);

    for (int i = 0; i < num_edges; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<int, std::vector<std::pair<int, int>>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_vertices = std::stoi(split_string[0]);
    std::vector<std::pair<int, int>> edges;

    for (int i = 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        edges.emplace_back(std::stoi(split_string[0]) - 1, std::stoi(split_string[1]) - 1);
    }

    return {num_vertices, edges};
}

#endif