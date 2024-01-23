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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(std::stoi(line));
    }

    return output;
}

std::string format_output(const std::vector<std::vector<int>> &solution)
{
    std::string output;
    for (const std::vector<int> &test_case : solution)
    {
        for (int i = 0; i < test_case.size(); i++)
        {
            output += std::to_string(test_case[i]);
            if (i != test_case.size() - 1)
            {
                output += ' ';
            }
        }
        output += '\n';
    }
    return output;
}

#endif