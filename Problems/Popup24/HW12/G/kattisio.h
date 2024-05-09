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
    std::getline(std::cin, line);
    int num_rooms = std::stoi(line);

    for (int i = 0; i < num_rooms; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<int> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> rooms;
    rooms.reserve(input.size());

    for (const std::string &s : input)
    {
        rooms.push_back(std::stoi(s));
    }

    return rooms;
}

std::string format_output(const int &solution)
{
    return std::to_string(solution) + '\n';
}

#endif