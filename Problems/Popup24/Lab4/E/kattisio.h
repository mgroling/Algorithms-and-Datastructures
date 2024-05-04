// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::vector<int>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>{});
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        for (int j = 0; j < split_string.size(); j++)
        {
            output[i].push_back(std::stoi(split_string[j]));
        }
    }

    return output;
}

std::string format_output(const std::vector<double> &solution)
{
    std::ostringstream output_stream;
    // set precision of doubles in this stream to 2 digits after the dot
    output_stream << std::fixed << std::setprecision(2);

    for (const double &sol : solution)
    {
        output_stream << sol << '\n';
    }

    return output_stream.str();
}

#endif