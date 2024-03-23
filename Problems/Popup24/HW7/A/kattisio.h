// Authors: Marc Gröling

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

    while (std::getline(std::cin, line))
    {
        output.push_back(line);
    }

    return output;
}

std::vector<std::string> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> output;

    for (int i = 0; i < input.size(); i++)
    {
        output.push_back(input[i]);
    }

    return output;
}

std::string format_output(const std::vector<std::string> &solution)
{
    std::string output = "";

    for (const std::string &partial : solution)
    {
        output += partial + '\n';
    }

    return output;
}

#endif