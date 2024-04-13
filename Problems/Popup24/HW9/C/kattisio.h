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
    int m = std::stoi(split(line, ' ')[1]);

    std::getline(std::cin, line);
    output.push_back(line);

    for (int i = 0; i < m; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<uint8_t>, std::vector<std::pair<uint16_t, uint16_t>>> parse_input(
    const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    std::vector<uint8_t> permutation;
    for (const std::string &elem : split_string)
    {
        permutation.push_back(std::stoi(elem));
    }

    std::vector<std::pair<uint16_t, uint16_t>> swaps;
    for (int i = 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        swaps.emplace_back(std::stoi(split_string[0]) - 1, std::stoi(split_string[1]) - 1);
    }

    return {permutation, swaps};
}

std::string format_output(const int8_t &solution)
{
    return std::to_string(solution) + '\n';
}

#endif