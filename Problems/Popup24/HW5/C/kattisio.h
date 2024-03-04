#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Position
{
    int row;
    int col;

    Position()
    {
    }

    Position(int row_, int col_)
    {
        row = row_;
        col = col_;
    }
};

struct Test_case
{
    int num_rows;
    int num_cols;
    std::vector<std::vector<char>> maze;
    Position start_position;
    std::vector<Position> alien_positions;

    Test_case(int num_rows_, int num_cols_, std::vector<std::vector<char>> maze_, Position start_position_,
              std::vector<Position> alien_positions_)
    {
        num_rows = num_rows_;
        num_cols = num_cols_;
        maze = maze_;
        start_position = start_position_;
        alien_positions = alien_positions_;
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
    output.push_back(line);

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
        int num_rows = std::stoi(split(line, ' ')[1]);
        for (int j = 0; j < num_rows; j++)
        {
            std::getline(std::cin, line);
            output.push_back(line);
        }
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;
    int num_test_cases = std::stoi(input[0]);
    std::vector<std::string> split_string;

    for (int i = 1; i < input.size();)
    {
        split_string = split(input[i], ' ');
        int num_rows = std::stoi(split_string[1]);
        int num_cols = std::stoi(split_string[0]);
        i++;

        std::vector<std::vector<char>> maze(num_rows, std::vector<char>(num_cols));
        Position start_position;
        std::vector<Position> alien_positions;
        for (int j = 0; j < num_rows; j++)
        {
            for (int k = 0; k < input[i + j].size(); k++)
            {
                maze[j][k] = input[i + j][k];

                if (input[i + j][k] == 'S')
                {
                    start_position = Position(j, k);
                }
                else if (input[i + j][k] == 'A')
                {
                    alien_positions.emplace_back(j, k);
                }
            }
        }
        i += num_rows;

        output.emplace_back(num_rows, num_cols, maze, start_position, alien_positions);
    }

    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output = "";

    for (const int &cost : solution)
    {
        output += std::to_string(cost);
        output += "\n";
    }

    return output;
}

#endif