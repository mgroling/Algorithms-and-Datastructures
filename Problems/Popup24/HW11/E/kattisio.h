#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
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
    int num_triangles = std::stoi(line);

    for (int i = 0; i < num_triangles; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::tuple<int, int, int>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::tuple<int, int, int>> output;
    output.reserve(input.size());
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        output.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]), std::stoi(split_string[2]));
    }

    return output;
}

std::string format_output(const double &solution)
{
    return std::to_string(solution) + '\n';
}

#endif