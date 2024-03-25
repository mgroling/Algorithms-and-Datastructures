#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_input()
{
    std::vector<std::string> output;
    std::string line;

    for (int i = 0; i < 2; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::string parse_input(const std::vector<std::string> &input)
{
    return input[1];
}

#endif