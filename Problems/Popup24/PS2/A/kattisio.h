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
    int num_agents = std::stoi(line);

    for (int i = 0; i < num_agents; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::vector<int>> parse_input(std::vector<std::string> input)
{
    int num_agents = std::stoi(input[0]);
    std::vector<std::string> split_string;
    std::vector<std::vector<int>> output(num_agents, std::vector<int>{});

    for (int i = 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        for (int j = 0; j < num_agents; j++)
        {
            output[i - 1].push_back(std::stoi(split_string[j]));
        }
    }

    return output;
}

#endif