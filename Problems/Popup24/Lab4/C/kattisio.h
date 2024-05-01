// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::vector<std::pair<int, int>> vertices;
    std::vector<std::pair<int, int>> query_points;

    Test_case(const std::vector<std::pair<int, int>> &vertices, const std::vector<std::pair<int, int>> &query_points)
    {
        this->vertices = vertices;
        this->query_points = query_points;
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
    std::vector<std::string> split_string;
    std::string line;
    std::getline(std::cin, line);

    while (line != "0")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size();)
    {
        int num_vertices = std::stoi(input[i]);
        i++;

        std::vector<std::pair<int, int>> vertices;
        for (int j = 0; j < num_vertices; j++)
        {
            split_string = split(input[i + j], ' ');
            vertices.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_vertices;

        int num_points = std::stoi(input[i]);
        i++;

        std::vector<std::pair<int, int>> points;
        for (int j = 0; j < num_points; j++)
        {
            split_string = split(input[i + j], ' ');
            points.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_points;

        output.emplace_back(vertices, points);
    }

    return output;
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &sol : solution)
    {
        if (sol == 0)
        {
            output += "on\n";
        }
        else if (sol == 1)
        {
            output += "in\n";
        }
        else
        {
            output += "out\n";
        }
    }

    return output;
}

#endif