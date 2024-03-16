// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    unsigned long long num1;
    unsigned long long num2;
    std::string operator_;
    unsigned long long modulus;

    Test_case(unsigned long long num1, unsigned long long num2, std::string operator_, unsigned long long modulo)
    {
        this->num1 = num1;
        this->num2 = num2;
        this->operator_ = operator_;
        this->modulus = modulus;
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

    while (line != "0 0")
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

    for (int i = 0; i < input.size();)
    {
        split_string = split(input[i++], ' ');
        unsigned long long modulus = std::stoull(split_string[0]);
        int num_tests = std::stoi(split_string[1]);

        for (int j = 0; j < num_tests; j++)
        {
            split_string = split(input[i + j], ' ');
            test_cases.emplace_back(std::stoull(split_string[0]), std::stoull(split_string[2]), split_string[1],
                                    modulus);
        }
    }

    return test_cases;
}

std::string format_output(const std::vector<unsigned long long> &solution)
{
    std::string output = "";

    for (const unsigned long long &answer : solution)
    {
        output += std::to_string(answer) + '\n';
    }

    return output;
}

#endif