#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_input()
{
    std::vector<std::string> output;
    std::string line;
    std::getline(std::cin, line);
    int num_elems = std::stoi(line);

    for (int i = 0; i < num_elems; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<int> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> output;

    for (const std::string &elem : input)
    {
        output.push_back(std::stoi(elem) - 1);
    }

    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &sol : solution)
    {
        output += std::to_string(sol) + '\n';
    }

    return output;
}

#endif