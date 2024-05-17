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
    std::getline(std::cin, line);
    output.push_back(line);

    return output;
}

std::vector<int> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> output;
    output.reserve(std::stoi(input[0]));
    std::vector<std::string> split_string = split(input[1], ' ');

    for (const std::string &elem : split_string)
    {
        output.push_back(std::stoi(elem));
    }

    return output;
}

std::string format_output(const std::pair<int, int> &solution)
{
    return std::to_string(solution.first) + ' ' + std::to_string(solution.second) + '\n';
}

#endif