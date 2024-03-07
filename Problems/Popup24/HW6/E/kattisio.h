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

    for (int i = 0; i < 3; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<int>, std::vector<int>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[1], ' ');
    std::vector<int> sum_rows;
    sum_rows.reserve(split_string.size());
    for (int i = 0; i < split_string.size(); i++)
    {
        sum_rows.push_back(std::stoi(split_string[i]));
    }

    split_string = split(input[2], ' ');
    std::vector<int> sum_cols;
    sum_cols.reserve(split_string.size());
    for (int i = 0; i < split_string.size(); i++)
    {
        sum_cols.push_back(std::stoi(split_string[i]));
    }

    return {sum_rows, sum_cols};
}

std::string format_output(const bool &solution)
{
    if (solution)
    {
        return "Yes\n";
    }
    return "No\n";
}

#endif