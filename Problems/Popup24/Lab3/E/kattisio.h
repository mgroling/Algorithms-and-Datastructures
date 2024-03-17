// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    unsigned long long a;
    unsigned long long n;
    unsigned long long b;
    unsigned long long m;

    Test_case(unsigned long long a, unsigned long long n, unsigned long long b, unsigned long long m)
    {
        this->a = a;
        this->n = n;
        this->b = b;
        this->m = m;
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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string;
    std::vector<Test_case> test_cases;

    for (int i = 0; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        test_cases.emplace_back(std::stoull(split_string[0]), std::stoull(split_string[1]),
                                std::stoull(split_string[2]), std::stoull(split_string[3]));
    }

    return test_cases;
}

std::string format_output(const std::vector<std::pair<unsigned long long, unsigned long long>> &solution)
{
    std::string output = "";

    for (const std::pair<unsigned long long, unsigned long long> &answer : solution)
    {
        output += std::to_string(answer.first) + ' ' + std::to_string(answer.second) + '\n';
    }

    return output;
}

#endif