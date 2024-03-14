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
    int num_queries = std::stoi(split(line, ' ')[1]);

    for (int i = 0; i < num_queries; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<int, std::vector<int>> parse_input(std::vector<std::string> input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int max_value = std::stoi(split_string[0]);
    std::vector<int> queries;

    for (int i = 1; i < input.size(); i++)
    {
        queries.push_back(std::stoi(input[i]));
    }

    return {max_value, queries};
}

std::string format_output(std::pair<int, std::vector<bool>> solution)
{
    std::string output = std::to_string(solution.first) + "\n";

    for (const bool &answer : solution.second)
    {
        if (answer)
        {
            output += "1";
        }
        else
        {
            output += "0";
        }
        output += "\n";
    }

    return output;
}

#endif