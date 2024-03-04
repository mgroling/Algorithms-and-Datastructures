#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Test_case
{
    int num_nodes;
    int start_node;
    int end_node;
    int time_delay;
    std::vector<int> george_path;
    std::vector<std::tuple<int, int, int>> edges;

    Test_case(int num_nodes_, int start_node_, int end_node_, int time_delay_, std::vector<int> george_path_,
              std::vector<std::tuple<int, int, int>> edges_)
    {
        num_nodes = num_nodes_;
        start_node = start_node_;
        end_node = end_node_;
        time_delay = time_delay_;
        george_path = george_path_;
        edges = edges_;
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
    int num_edges = std::stoi(split(line, ' ')[1]);

    for (int i = 0; i < num_edges + 2; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(std::vector<std::string> input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_vertices = std::stoi(split_string[0]);
    int num_edges = std::stoi(split_string[1]);
    split_string = split(input[1], ' ');
    int start_vertex = std::stoi(split_string[0]) - 1;
    int end_vertex = std::stoi(split_string[1]) - 1;
    int delay = std::stoi(split_string[2]);
    split_string = split(input[2], ' ');
    std::vector<int> george_path;
    for (int i = 0; i < split_string.size(); i++)
    {
        george_path.push_back(std::stoi(split_string[i]) - 1);
    }

    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 3; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        edges.emplace_back(std::stoi(split_string[0]) - 1, std::stoi(split_string[1]) - 1, std::stoi(split_string[2]));
    }

    return Test_case(num_vertices, start_vertex, end_vertex, delay, george_path, edges);
}

#endif