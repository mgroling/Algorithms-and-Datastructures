#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    int length_string;
    std::vector<std::pair<int, std::string>> suffixes;

    Test_case(int length_string, std::vector<std::pair<int, std::string>> suffixes)
    {
        this->length_string = length_string;
        this->suffixes = suffixes;
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
    output.push_back(line);
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
        std::vector<std::string> split_string = split(line, ' ');
        for (int j = 0; j < std::stoi(split_string[1]); j++)
        {
            std::getline(std::cin, line);
            output.push_back(line);
        }
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;
    output.reserve(std::stoi(input[0]));
    std::vector<std::string> split_string;

    int i = 1;
    while (i < input.size())
    {
        split_string = split(input[i++], ' ');
        int length_string = std::stoi(split_string[0]);
        int num_suffixes = std::stoi(split_string[1]);
        std::vector<std::pair<int, std::string>> suffixes;
        suffixes.reserve(num_suffixes);

        for (int j = 0; j < num_suffixes; j++)
        {
            split_string = split(input[i + j], ' ');
            suffixes.emplace_back(std::stoi(split_string[0]), split_string[1]);
        }
        i += num_suffixes;
        output.emplace_back(length_string, suffixes);
    }

    return output;
}

std::string format_output(const std::vector<std::string> &solution)
{
    std::string output = "";

    for (const std::string &sub_solution : solution)
    {
        output += sub_solution + '\n';
    }

    return output;
}

#endif