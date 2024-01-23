#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Test_case
{
    std::vector<std::string> sentence;
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

    for (int i = 0; i < num_test_cases << 1; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }
    return output;
}

std::vector<std::tuple<Test_case, Test_case>> parse_input(const std::vector<std::string> &input)
{
    int num_test_cases = input.size();
    std::vector<std::tuple<Test_case, Test_case>> output;
    output.reserve(num_test_cases);

    for (int i = 0; i < num_test_cases; i += 2)
    {
        Test_case case_1;
        std::vector<std::string> split_string = split(input[i], ' ');
        case_1.sentence.insert(case_1.sentence.end(), split_string.begin(), split_string.end());

        Test_case case_2;
        split_string = split(input[i + 1], ' ');
        case_2.sentence.insert(case_2.sentence.end(), split_string.begin(), split_string.end());

        output.emplace_back(case_1, case_2);
    }
    return output;
}

std::string format_output(const std::vector<std::vector<std::string>> &solution)
{
    std::string output;
    for (const std::vector<std::string> &sentence : solution)
    {
        std::string formatted_sentence;
        for (int i = 0; i < sentence.size(); i++)
        {
            output += sentence[i];
            if (i != sentence.size() - 1)
            {
                output += ' ';
            }
        }
        output += "\n";
    }
    return output;
}

#endif