// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_input()
{
    std::vector<std::string> output;
    std::string line;

    while (std::getline(std::cin, line))
    {
        output.push_back(line);
    }

    return output;
}

std::vector<std::pair<std::string, std::string>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::pair<std::string, std::string>> output;

    for (int i = 0; i < input.size(); i += 2)
    {
        output.emplace_back(input[i], input[i + 1]);
    }

    return output;
}

std::string format_output(const std::vector<std::vector<int>> &solution)
{
    std::string output = "";

    for (const std::vector<int> &test_case : solution)
    {
        for (const int &index : test_case)
        {
            output += std::to_string(index) + ' ';
        }
        output += '\n';
    }

    return output;
}

#endif