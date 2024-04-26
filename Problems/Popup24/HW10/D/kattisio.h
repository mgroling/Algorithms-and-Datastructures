#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::vector<std::pair<int, int>> items;
    int size_dictionary;

    Test_case(std::vector<std::pair<int, int>> items, int size_dictionary)
    {
        this->items = items;
        this->size_dictionary = size_dictionary;
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

    for (int i = 0; i < num_test_cases; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
        std::vector<std::string> split_string = split(line, ' ');
        int num_items = std::stoi(split(line, ' ')[0]);

        for (int j = 0; j < num_items; j++)
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
    std::vector<std::string> split_string;

    for (int i = 0; i < input.size();)
    {
        split_string = split(input[i], ' ');
        i++;
        int num_items = std::stoi(split_string[0]);
        int size_dictionary = std::stoi(split_string[1]);

        std::vector<std::pair<int, int>> items;
        for (int j = 0; j < num_items; j++)
        {
            split_string = split(input[i + j], ' ');
            items.emplace_back(std::stoi(split_string[0]), std::stoi(split_string[1]));
        }
        i += num_items;

        output.emplace_back(items, size_dictionary);
    }

    return output;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output;

    for (const bool &success : solution)
    {
        output += (success ? "successful hashing\n" : "rehash necessary\n");
    }

    return output;
}

#endif