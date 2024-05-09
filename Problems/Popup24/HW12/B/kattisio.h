#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

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

    for (int i = 0; i < 3; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::vector<int>, std::vector<int>> parse_input(const std::vector<std::string> &input)
{
    int num_hands = std::stoi(input[0]);
    std::vector<int> hands1;
    hands1.reserve(num_hands);
    std::vector<int> hands2;
    hands2.reserve(num_hands);

    std::vector<std::string> split_string = split(input[1], ' ');
    for (int i = 0; i < split_string.size(); i++)
    {
        hands1.push_back(std::stoi(split_string[i]));
    }

    split_string = split(input[2], ' ');
    for (int i = 0; i < split_string.size(); i++)
    {
        hands2.push_back(std::stoi(split_string[i]));
    }

    return {hands1, hands2};
}

std::string format_output(const bool &solution)
{
    if (solution)
    {
        return "possible\n";
    }
    return "impossible\n";
}

#endif