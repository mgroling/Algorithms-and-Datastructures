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

    return output;
}

long long parse_input(const std::vector<std::string> &input)
{
    return std::stoll(input[0]);
}

std::string format_output(const std::pair<std::string, std::string> &solution)
{
    return solution.first + '\n' + solution.second + '\n';
}

#endif