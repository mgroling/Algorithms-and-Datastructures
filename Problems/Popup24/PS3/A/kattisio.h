#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::string sentence;
    std::vector<std::pair<int, int>> queries;
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
    std::getline(std::cin, line);
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string;

    std::vector<std::pair<int, int>> queries;
    for (int i = 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        queries.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
    }

    return Test_case{input[0], queries};
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output = "";

    for (const int &sub_solution : solution)
    {
        output += std::to_string(sub_solution) + '\n';
    }

    return output;
}

#endif