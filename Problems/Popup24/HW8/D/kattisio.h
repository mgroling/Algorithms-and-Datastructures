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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<long long> parse_input(const std::vector<std::string> &input)
{
    std::vector<long long> output;

    for (int i = 0; i < input.size(); i++)
    {
        output.push_back(std::stoll(input[i]));
    }

    return output;
}

std::string format_output(const std::vector<long long> &solution)
{
    std::string output = "";

    for (const long long &partial : solution)
    {
        output += std::to_string(partial) + '\n';
    }

    return output;
}

#endif