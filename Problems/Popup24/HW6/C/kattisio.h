#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    int num_vertices;
    std::vector<int> fuel_prices;
    std::vector<std::tuple<int, int, int>> edges;
    std::vector<std::tuple<int, int, int>> queries;

    Test_case(int num_vertices, std::vector<int> fuel_prices, std::vector<std::tuple<int, int, int>> edges,
              std::vector<std::tuple<int, int, int>> queries)
    {
        this->num_vertices = num_vertices;
        this->fuel_prices = fuel_prices;
        this->edges = edges;
        this->queries = queries;
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

    for (int i = 0; i < num_edges + 1; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    std::getline(std::cin, line);
    output.push_back(line);
    int num_queries = std::stoi(line);

    for (int i = 0; i < num_queries; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_vertices = std::stoi(split_string[0]);
    int num_edges = std::stoi(split_string[1]);

    std::vector<int> fuel_prices;
    split_string = split(input[1], ' ');
    for (int i = 0; i < split_string.size(); i++)
    {
        fuel_prices.push_back(std::stoi(split_string[i]));
    }

    std::vector<std::tuple<int, int, int>> edges;
    edges.reserve(num_edges);
    for (int i = 2; i < num_edges + 2; i++)
    {
        split_string = split(input[i], ' ');
        edges.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]), std::stoi(split_string[2]));
    }

    std::vector<std::tuple<int, int, int>> queries;
    for (int i = num_edges + 3; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        queries.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]), std::stoi(split_string[2]));
    }

    return Test_case(num_vertices, fuel_prices, edges, queries);
}

std::string format_output(const std::vector<int> &solution)
{
    std::string output;

    for (const int &query_solution : solution)
    {
        if (query_solution >= 0)
        {
            output += std::to_string(query_solution) + "\n";
        }
        else
        {
            output += "impossible\n";
        }
    }

    return output;
}

#endif