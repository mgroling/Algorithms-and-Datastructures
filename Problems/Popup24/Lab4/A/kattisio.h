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
    std::getline(std::cin, line);
    output.push_back(line);
    std::getline(std::cin, line);
    output.push_back(line);
    int num_queries = std::stoi(line);

    for (int i = 0; i < num_queries; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::string, std::vector<std::pair<int, int>>> parse_input(const std::vector<std::string> &input)
{
    std::string word = input[0];
    std::vector<std::pair<int, int>> queries;
    std::vector<std::string> split_string;

    for (int i = 2; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        queries.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
    }

    return {word, queries};
}

std::string format_output(const std::vector<uint64_t> &solution)
{
    std::string output;

    for (const uint64_t &hash : solution)
    {
        output += std::to_string(hash) + '\n';
    }

    return output;
}

#endif