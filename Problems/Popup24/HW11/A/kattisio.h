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
    output.push_back(line);
    std::vector<std::string> split_string = split(line, ' ');
    int num_objects = std::stoi(split_string[0]) + std::stoi(split_string[1]);

    for (int i = 0; i < num_objects; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<Point<long double>>, std::vector<Point<long double>>> parse_input(
    const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_toys = std::stoi(split_string[0]);
    int num_trees = std::stoi(split_string[1]);
    std::vector<Point<long double>> toys;
    toys.reserve(num_toys);
    std::vector<Point<long double>> trees;
    trees.reserve(num_trees);

    for (int i = 1; i < num_toys + 1; i++)
    {
        split_string = split(input[i], ' ');
        toys.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
    }

    for (int i = num_toys + 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        trees.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
    }

    return {toys, trees};
}

std::string format_output(const long double &solution)
{
    return std::to_string(solution) + '\n';
}

#endif