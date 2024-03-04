// Authors: Marc Gröling

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
    std::vector<std::tuple<int, int, int>> edges;
    std::vector<int> queries;

    Test_case(int num_nodes_, int start_node_, std::vector<std::tuple<int, int, int>> edges_, std::vector<int> queries_)
    {
        num_nodes = num_nodes_;
        start_node = start_node_;
        edges = edges_;
        queries = queries_;
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

    while (line != "0 0 0 0")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<Test_case> parse_input(std::vector<std::string> input)
{
    std::vector<Test_case> output;
    std::vector<std::string> split_string;
    for (int i = 0; i < input.size();)
    {
        split_string = split(input[i++], ' ');
        int num_nodes = std::stoi(split_string[0]);
        int num_edges = std::stoi(split_string[1]);
        std::vector<std::tuple<int, int, int>> edges;
        edges.reserve(num_edges);
        int num_queries = std::stoi(split_string[2]);
        std::vector<int> queries;
        queries.reserve(num_queries);
        int start_node = std::stoi(split_string[3]);

        for (int j = 0; j < num_edges; j++)
        {
            split_string = split(input[i + j], ' ');

            edges.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]), std::stoi(split_string[2]));
        }
        i += num_edges;

        for (int j = 0; j < num_queries; j++)
        {
            queries.push_back(std::stoi(input[i + j]));
        }
        i += num_queries;

        output.emplace_back(num_nodes, start_node, edges, queries);
    }
    return output;
}

#endif