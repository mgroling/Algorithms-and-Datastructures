// Authors: Marc Gröling

#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::string text;
    std::vector<std::string> words;

    Test_case(std::string text, std::vector<std::string> words)
    {
        this->text = text;
        this->words = words;
    }
};

std::vector<std::string> read_input()
{
    std::vector<std::string> output;
    std::string line;

    while (std::getline(std::cin, line))
    {
        output.push_back(line);
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;

    for (int i = 0; i < input.size(); i++)
    {
        int num_words = std::stoi(input[i++]);
        std::vector<std::string> words;
        words.reserve(num_words);

        for (int j = 0; j < num_words; j++)
        {
            words.push_back(input[i + j]);
        }
        i += num_words;

        output.emplace_back(input[i], words);
    }

    return output;
}

std::string format_output(const std::vector<std::vector<int>> &solution)
{
    std::string output = "";

    for (const std::vector<int> &test_case : solution)
    {
        for (const int &index : test_case)
        {
            output += std::to_string(index) + ' ';
        }
        output += '\n';
    }

    return output;
}

#endif