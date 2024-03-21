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

    int num_tiles = std::stoi(split(line, ' ')[0]);
    for (int i = 0; i < num_tiles; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::pair<std::string, std::vector<std::string>> parse_input(const std::vector<std::string> &input)
{
    std::string street = input[1];
    std::vector<std::string> tiles;
    tiles.reserve(input.size() - 3);

    for (int i = 3; i < input.size(); i++)
    {
        tiles.push_back(input[i]);
    }

    return {street, tiles};
}

#endif