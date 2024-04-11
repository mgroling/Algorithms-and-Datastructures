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
    int num_test_cases = std::stoi(line);

    for (int i = 0; i < num_test_cases * 5; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<std::string> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> output;
    output.reserve(input.size() / 5);

    for (int i = 0; i < input.size(); i += 5)
    {
        std::string temp;
        for (int j = 0; j < 5; j++)
        {
            temp += input[i + j];
        }
        output.push_back(temp);
    }

    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output = "";

    for (const int &sub_solution : solution)
    {
        if (sub_solution == -1)
        {
            output += "Unsolvable in less than 11 move(s).\n";
        }
        else
        {
            output += "Solvable in " + std::to_string(sub_solution) + " move(s).\n";
        }
    }

    return output;
}

#endif