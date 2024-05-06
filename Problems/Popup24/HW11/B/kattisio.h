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
    std::getline(std::cin, line);
    output.push_back(line);
    int num_vertices = std::stoi(line);

    for (int i = 0; i < num_vertices; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<Point<long double>>, long double> parse_input(const std::vector<std::string> &input)
{
    long double min_area = std::stold(input[0]);
    std::vector<std::string> split_string;
    int num_vertices = std::stoi(input[1]);
    std::vector<Point<long double>> vertices;
    vertices.reserve(num_vertices);

    for (int i = 2; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        vertices.emplace_back(std::stold(split_string[0]), std::stold(split_string[1]));
    }

    return {vertices, min_area};
}

std::string format_output(const std::pair<int, std::vector<long double>> &solution)
{
    std::string output;

    output += std::to_string(solution.first) + '\n';

    for (const long double &coordinate : solution.second)
    {
        output += std::to_string(coordinate) + '\n';
    }

    return output;
}

#endif