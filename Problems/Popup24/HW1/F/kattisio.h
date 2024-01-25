#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

std::vector<int> read_input()
{
    std::vector<int> output;
    std::string line;
    std::getline(std::cin, line);
    int num_weights = std::stoi(line);

    for (int i = 0; i < num_weights; i++)
    {
        std::getline(std::cin, line);
        output.push_back(std::stoi(line));
    }

    return output;
}

#endif