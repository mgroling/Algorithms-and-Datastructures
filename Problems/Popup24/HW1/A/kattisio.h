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

std::tuple<long double, long double, std::vector<long double>> read_input()
{
    std::vector<long double> output;
    std::string line;
    std::getline(std::cin, line);
    int num_trees = std::stoi(line);

    std::getline(std::cin, line);
    std::vector<std::string> split_string = split(line, ' ');
    long double length = std::stold(split_string[0]);
    long double width = std::stold(split_string[1]);

    for (int i = 0; i < num_trees; i++)
    {
        std::getline(std::cin, line);
        output.push_back(std::stold(line));
    }

    return std::tuple{length, width, output};
}

#endif