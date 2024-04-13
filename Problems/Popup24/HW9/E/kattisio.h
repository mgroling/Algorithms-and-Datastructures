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
    for (int i = 0; i < 4; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::string parse_input(const std::vector<std::string> &input)
{
    std::string output;

    for (const std::string &elem : input)
    {
        output += elem;
    }

    return output;
}

std::string format_output(const int8_t &solution)
{
    return std::to_string(solution) + '\n';
}

#endif