#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
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
    int num_vertices = std::stoi(split(line, ' ')[0]);

    for (int i = 0; i < num_vertices; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::string> parse_input(std::vector<std::string> input)
{
    std::vector<std::string> output;
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_vertices = std::stoi(split_string[0]);

    for (int i = 1; i < num_vertices + 1; i++)
    {
        output.push_back(input[i]);
    }

    return output;
}

std::string format_output(std::pair<int, std::vector<std::pair<int, int>>> solution)
{
    std::string output = "";
    output += std::to_string(solution.first);
    output += "\n";

    for (const std::pair<int, int> edge : solution.second)
    {
        output += std::to_string(edge.first);
        output += " ";
        output += std::to_string(edge.second);
        output += "\n";
    }

    return output;
}

#endif