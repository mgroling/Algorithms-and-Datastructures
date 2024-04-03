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

    while (line != ".")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<std::string> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> output;
    std::vector<std::string> split_string;

    for (const std::string &elem : input)
    {
        split_string = split(elem, '.');
        output.emplace_back(split_string[0] + split_string[1]);
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