#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    int num_rows_target;
    int num_cols_target;
    int num_rows;
    int num_cols;
    std::vector<std::vector<bool>> target;
    std::vector<std::vector<bool>> painting;
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
    std::vector<std::string> split_string = split(line, ' ');
    int num_rows_target = std::stoi(split_string[0]);
    int num_rows_painting = std::stoi(split_string[2]);

    for (int i = 0; i < num_rows_target + num_rows_painting; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');

    int num_rows_target = std::stoi(split_string[0]);
    int num_cols_target = std::stoi(split_string[1]);
    int num_rows_painting = std::stoi(split_string[2]);
    int num_cols_painting = std::stoi(split_string[3]);

    std::vector<std::vector<bool>> target;
    for (int i = 1; i < num_rows_target + 1; i++)
    {
        target.push_back(std::vector<bool>{});
        for (int j = 0; j < input[i].size(); j++)
        {
            target.back().push_back(input[i][j] == 'x' ? true : false);
        }
    }

    std::vector<std::vector<bool>> painting;
    for (int i = 1 + num_rows_target; i < input.size(); i++)
    {
        painting.push_back(std::vector<bool>{});
        for (int j = 0; j < input[i].size(); j++)
        {
            painting.back().push_back(input[i][j] == 'x' ? true : false);
        }
    }

    return Test_case{num_rows_target, num_cols_target, num_rows_painting, num_cols_painting, target, painting};
}

std::string format_output(const int &solution)
{
    return std::to_string(solution) + '\n';
}

#endif