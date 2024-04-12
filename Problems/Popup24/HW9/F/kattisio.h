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

std::vector<std::string> parse_input(const std::vector<std::string> &input)
{
    return input;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output = "";

    for (const bool &sub_solution : solution)
    {
        if (sub_solution)
        {
            output += "tautology\n";
        }
        else
        {
            output += "not\n";
        }
    }

    return output;
}

#endif