// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Test_case
{
    std::vector<long long> coefficients;
    std::vector<long long> initial_values;
    std::vector<std::pair<long long, long long>> queries;

    Test_case(std::vector<long long> coefficients, std::vector<long long> initial_values,
              std::vector<std::pair<long long, long long>> queries)
    {
        this->coefficients = coefficients;
        this->initial_values = initial_values;
        this->queries = queries;
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

    for (int i = 0; i < 4; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    int num_queries = std::stoi(line);
    for (int i = 0; i < num_queries; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string;
    std::vector<long long> coefficients;
    split_string = split(input[1], ' ');
    for (int i = 0; i < split_string.size(); i++)
    {
        coefficients.push_back(std::stoll(split_string[i]));
    }

    std::vector<long long> initial_values;
    split_string = split(input[2], ' ');
    for (int i = 0; i < split_string.size(); i++)
    {
        initial_values.push_back(std::stoll(split_string[i]));
    }

    std::vector<std::pair<long long, long long>> queries;
    for (int i = 4; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        queries.emplace_back(std::stoll(split_string[0]), std::stoll(split_string[1]));
    }

    return Test_case(coefficients, initial_values, queries);
}

std::string format_output(const std::vector<long long> &solution)
{
    std::string output = "";

    for (const long long &answer : solution)
    {
        output += std::to_string(answer) + '\n';
    }

    return output;
}

#endif