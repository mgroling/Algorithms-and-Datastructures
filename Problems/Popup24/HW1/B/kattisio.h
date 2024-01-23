#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    int num_cokes_to_buy;
    int num_1_coins;
    int num_5_coins;
    int num_10_coins;

    Test_case(int a, int b, int c, int d)
    {
        num_cokes_to_buy = a;
        num_1_coins = b;
        num_5_coins = c;
        num_10_coins = d;
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
    std::vector<Test_case> output;

    for (const std::string &test_case : input)
    {
        std::vector<std::string> split_string = split(test_case, ' ');
        output.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]), std::stoi(split_string[2]),
                            std::stoi(split_string[3]));
    }
    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &num_coins_used : solution)
    {
        output += std::to_string(num_coins_used) + '\n';
    }
    return output;
}

#endif