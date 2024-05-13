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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
        int num_friendships = std::stoi(line);

        for (int j = 0; j < num_friendships; j++)
        {
            std::getline(std::cin, line);
            output.push_back(line);
        }
    }

    return output;
}

std::vector<std::vector<std::pair<std::string, std::string>>> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::vector<std::pair<std::string, std::string>>> output(
        std::stoi(input[0]), std::vector<std::pair<std::string, std::string>>{});
    std::vector<std::string> split_string;

    int index_test_case = 0;
    for (int i = 1; i < input.size();)
    {
        int num_friendships = std::stoi(input[i]);
        i++;

        for (int j = 0; j < num_friendships; j++)
        {
            split_string = split(input[i + j], ' ');
            output[index_test_case].emplace_back(split_string[0], split_string[1]);
        }
        i += num_friendships;
        index_test_case++;
    }

    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &sol : solution)
    {
        output += std::to_string(sol) + '\n';
    }

    return output;
}

#endif