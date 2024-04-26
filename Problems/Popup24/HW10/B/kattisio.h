#ifndef kattisio
#define kattisio

#include <algorithm>
#include <cctype>
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

    while (line != "")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<std::string> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> output;

    for (const std::string &sentence : input)
    {
        output.push_back("");
        for (const char &letter : sentence)
        {
            if (letter != ' ')
            {
                output.back().push_back(letter);
            }
        }
    }

    return output;
}

std::string format_output(const std::vector<std::vector<int>> &solution)
{
    std::string output;

    for (const std::vector<int> &partial_solution : solution)
    {
        for (const int &num_occurences : partial_solution)
        {
            output += std::to_string(num_occurences) + '\n';
        }
        output += '\n';
    }

    return output;
}

#endif