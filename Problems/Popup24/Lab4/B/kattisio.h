// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Test_case
{
    std::vector<std::pair<int, int>> points;

    Test_case(std::vector<std::pair<int, int>> points)
    {
        this->points = points;
    }
};

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

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size();)
    {
        int num_points = std::stoi(input[i]);
        i++;

        std::vector<std::pair<int, int>> points;
        points.reserve(num_points);
        for (int j = 0; j < num_points; j++)
        {
            split_string = split(input[i + j], ' ');
            points.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_points;

        output.emplace_back(points);
    }

    return output;
}

std::string format_output(const std::vector<std::pair<bool, double>> &solution)
{
    std::ostringstream output_stream;

    for (const std::pair<bool, double> &partial_solution : solution)
    {
        // Convert double to string with precision 1
        output_stream << (partial_solution.first ? "CW " : "CCW ") << std::fixed << std::setprecision(1)
                      << partial_solution.second << '\n';
    }

    return output_stream.str();
}

#endif