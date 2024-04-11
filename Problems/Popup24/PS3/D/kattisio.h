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

    while (line != "0")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<int> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> output;

    for (int i = 0; i < input.size(); i++)
    {
        output.push_back(std::stoi(input[i]));
    }

    return output;
}

std::string format_output(const std::vector<std::pair<int, int>> &solution)
{
    std::string output = "";

    for (const std::pair<int, int> &sub_solution : solution)
    {
        output += std::to_string(sub_solution.first) + ' ' + std::to_string(sub_solution.second) + '\n';
    }

    return output;
}

#endif