// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::string text;
    std::vector<int> indices;

    Test_case(std::string text, std::vector<int> indices)
    {
        this->text = text;
        this->indices = indices;
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

    while (std::getline(std::cin, line))
    {
        output.push_back(line);
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;

    for (int i = 0; i < input.size(); i += 2)
    {
        std::string text = input[i];
        std::vector<std::string> split_string = split(input[i + 1], ' ');
        int num_indices = std::stoi(split_string[0]);
        std::vector<int> indices;
        indices.reserve(num_indices);

        for (int j = 1; j < split_string.size(); j++)
        {
            indices.push_back(std::stoi(split_string[j]));
        }
        output.emplace_back(text, indices);
    }

    return output;
}

std::string format_output(const std::vector<std::vector<int>> &solution)
{
    std::string output = "";

    for (const std::vector<int> &test_case : solution)
    {
        for (const int &index : test_case)
        {
            output += std::to_string(index) + ' ';
        }
        output += '\n';
    }

    return output;
}

#endif