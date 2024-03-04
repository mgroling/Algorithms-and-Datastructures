#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Test_case
{
    int num_floors;
    std::vector<std::pair<int, int>> elevators;

    Test_case(int num_floors_, std::vector<std::pair<int, int>> elevators_)
    {
        num_floors = num_floors_;
        elevators = elevators_;
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
        int num_elevators = std::stoi(split_string[1]);

        for (int j = 0; j < num_elevators; j++)
        {
            std::getline(std::cin, line);
            output.push_back(line);
        }
    }

    return output;
}

std::vector<Test_case> parse_input(std::vector<std::string> input)
{
    std::vector<Test_case> output;
    int num_test_cases = std::stoi(input[0]);

    for (int i = 1; i < input.size();)
    {
        std::vector<std::string> split_string = split(input[i], ' ');
        i++;
        int num_floors = std::stoi(split_string[0]);
        int num_elevators = std::stoi(split_string[1]);
        std::vector<std::pair<int, int>> elevators;
        elevators.reserve(num_elevators);

        for (int j = 0; j < num_elevators; j++)
        {
            split_string = split(input[i + j], ' ');
            elevators.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_elevators;

        output.emplace_back(num_floors, elevators);
    }

    return output;
}

std::string format_output(const std::vector<std::pair<int, int>> &solution)
{
    std::string output = "";
    for (const std::pair<int, int> &partial_solution : solution)
    {
        output += std::to_string(partial_solution.first);
        output += " ";
        output += std::to_string(partial_solution.second);
        output += "\n";
    }
    return output;
}

#endif