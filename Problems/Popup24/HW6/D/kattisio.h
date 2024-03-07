#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    int num_vertices;
    std::vector<std::pair<int, int>> one_way_edges;
    std::vector<std::pair<int, int>> two_way_edges;

    Test_case(int num_vertices, std::vector<std::pair<int, int>> one_way_edges,
              std::vector<std::pair<int, int>> two_way_edges)
    {
        this->num_vertices = num_vertices;
        this->one_way_edges = one_way_edges;
        this->two_way_edges = two_way_edges;
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
        int num_edges = std::stoi(split(line, ' ')[1]);
        for (int j = 0; j < num_edges; j++)
        {
            std::getline(std::cin, line);
            output.push_back(line);
        }
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    int num_test_cases = std::stoi(input[0]);
    std::vector<Test_case> test_cases;
    test_cases.reserve(num_test_cases);
    std::vector<std::string> split_string;

    for (int i = 1; i < input.size();)
    {
        split_string = split(input[i], ' ');
        int num_vertices = std::stoi(split_string[0]);
        int num_edges = std::stoi(split_string[1]);
        std::vector<std::pair<int, int>> one_way_edges;
        std::vector<std::pair<int, int>> two_way_edges;
        i++;

        for (int j = 0; j < num_edges; j++)
        {
            split_string = split(input[i + j], ' ');
            if (split_string[2] == "1")
            {
                one_way_edges.emplace_back(std::stoi(split_string[0]) - 1, std::stoi(split_string[1]) - 1);
            }
            else
            {
                two_way_edges.emplace_back(std::stoi(split_string[0]) - 1, std::stoi(split_string[1]) - 1);
            }
        }
        i += num_edges;

        test_cases.emplace_back(num_vertices, one_way_edges, two_way_edges);
    }

    return test_cases;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output = "";

    for (const bool &sub_solution : solution)
    {
        if (sub_solution)
        {
            output += "possible\n";
        }
        else
        {
            output += "impossible\n";
        }
    }

    return output;
}

#endif