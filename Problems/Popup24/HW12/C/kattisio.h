#ifndef kattisio
#define kattisio

#include "geometry.h"

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
    int num_line_segments = std::stoi(line);

    for (int i = 0; i < num_line_segments; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::pair<Point<long double>, Point<long double>>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string;
    std::vector<std::pair<Point<long double>, Point<long double>>> line_segments;
    line_segments.reserve(input.size());

    for (const std::string &line : input)
    {
        split_string = split(line, ' ');
        line_segments.emplace_back(Point<long double>(std::stoi(split_string[0]), std::stoi(split_string[1])),
                                   Point<long double>(std::stoi(split_string[2]), std::stoi(split_string[3])));
    }

    return line_segments;
}

std::string format_output(const int &solution)
{
    return std::to_string(solution) + '\n';
}

#endif