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
    output.push_back(line);
    int num_sequences = std::stoi(line);

    for (int i = 0; i < num_sequences; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::vector<int>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::vector<int>> sequences;
    int num_sequences = std::stoi(input[0]);
    sequences.reserve(num_sequences);

    for (int i = 1; i < input.size(); i++)
    {
        std::vector<int> sequence;
        std::vector<std::string> split_string = split(input[i], ' ');
        for (int j = 1; j < split_string.size(); j++)
        {
            sequence.emplace_back(std::stoi(split_string[j]));
        }
        sequences.emplace_back(sequence);
    }

    return sequences;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &elem : solution)
    {
        output += std::to_string(elem) + ' ';
    }
    output += '\n';

    return output;
}

#endif