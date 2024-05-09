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
    std::getline(std::cin, line);
    int num_data_sets = std::stoi(line);

    for (int i = 0; i < num_data_sets; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<int, std::vector<int>> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> data_sets;
    data_sets.reserve(input.size());
    int max_n = 2;

    for (int i = 0; i < input.size(); i++)
    {
        int n = std::stoi(split(input[i], ' ')[1]);
        max_n = std::max(max_n, n);
        data_sets.push_back(n);
    }

    return {max_n, data_sets};
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    int index = 1;
    for (const int &value : solution)
    {
        output += std::to_string(index) + ' ' + std::to_string(value) + '\n';
        index++;
    }

    return output;
}

#endif