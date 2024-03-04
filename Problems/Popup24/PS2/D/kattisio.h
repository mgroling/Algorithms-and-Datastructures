#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Test_case
{
    int num_x_grid;
    int num_y_grid;
    std::pair<int, int> start_pos;
    std::pair<int, int> end_pos;
    std::vector<std::pair<int, int>> bases;

    Test_case(int num_rows_grid_, int num_cols_grid_, std::pair<int, int> start_pos_, std::pair<int, int> end_pos_,
              std::vector<std::pair<int, int>> bases_)
    {
        num_x_grid = num_rows_grid_;
        num_y_grid = num_cols_grid_;
        start_pos = start_pos_;
        end_pos = end_pos_;
        bases = bases_;
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
    int num_bases = std::stoi(split(line, ' ')[0]);

    for (int i = 0; i < num_bases + 1; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(std::vector<std::string> input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_bases = std::stoi(split_string[0]);
    int num_x = std::stoi(split_string[1]);
    int num_y = std::stoi(split_string[2]);
    split_string = split(input[1], ' ');
    std::pair<int, int> start_pos{std::stoi(split_string[0]), std::stoi(split_string[1])};
    std::pair<int, int> end_pos{std::stoi(split_string[2]), std::stoi(split_string[3])};
    std::vector<std::pair<int, int>> bases;

    for (int i = 2; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        bases.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
    }

    return Test_case(num_x, num_y, start_pos, end_pos, bases);
}

#endif