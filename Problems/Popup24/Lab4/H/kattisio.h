// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include "../geometry.h"

#include <iomanip>
#include <iostream>
#include <sstream>
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

std::vector<std::vector<Point<int>>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::vector<Point<int>>> output;
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size();)
    {
        int num_points = std::stoi(input[i]);
        i++;

        output.push_back(std::vector<Point<int>>{});
        for (int j = 0; j < num_points; j++)
        {
            split_string = split(input[i + j], ' ');
            output.back().emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_points;
    }

    return output;
}

std::string format_output(const std::vector<std::vector<Point<int>>> &solution)
{
    std::string output;

    for (const std::vector<Point<int>> test_case : solution)
    {
        output += std::to_string(test_case.size()) + '\n';
        for (const Point<int> &p : test_case)
        {
            output += std::to_string(p.x) + ' ' + std::to_string(p.y) + '\n';
        }
    }

    return output;
}

#endif