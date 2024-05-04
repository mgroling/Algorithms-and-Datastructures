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

std::vector<std::vector<Point<double>>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::vector<Point<double>>> output;
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size();)
    {
        int num_points = std::stoi(input[i]);
        i++;

        output.push_back(std::vector<Point<double>>{});
        for (int j = 0; j < num_points; j++)
        {
            split_string = split(input[i + j], ' ');
            output.back().emplace_back(std::stod(split_string[0]), std::stod(split_string[1]));
        }
        i += num_points;
    }

    return output;
}

std::string format_output(const std::vector<std::vector<double>> &solution)
{
    std::ostringstream output_stream;
    // set precision of doubles in this stream to 2 digits after the dot
    output_stream << std::fixed << std::setprecision(2);

    for (const std::vector<double> &sol : solution)
    {
        for (const double &s : sol)
        {
            output_stream << s << ' ';
        }
        output_stream << '\n';
    }

    return output_stream.str();
}

#endif