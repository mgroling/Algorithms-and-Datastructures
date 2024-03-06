#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::vector<std::string> words;

    Test_case(std::vector<std::string> words)
    {
        this->words = words;
    }
};

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
        int num_words = std::stoi(line);
        for (int j = 0; j < num_words; j++)
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

    for (int i = 1; i < input.size();)
    {
        int num_words = std::stoi(input[i]);
        std::vector<std::string> words;
        words.reserve(num_words);
        i++;

        for (int j = 0; j < num_words; j++)
        {
            words.push_back(input[i + j]);
        }
        i += num_words;

        test_cases.emplace_back(words);
    }

    return test_cases;
}

#endif