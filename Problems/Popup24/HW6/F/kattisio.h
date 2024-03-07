#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Test_case
{
    std::vector<std::pair<int, std::vector<int>>> rooms;

    Test_case(std::vector<std::pair<int, std::vector<int>>> rooms)
    {
        this->rooms = rooms;
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

    while (line != "-1")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<Test_case> parse_input(const std::vector<std::string> &input)
{
    std::vector<Test_case> output;
    std::vector<std::string> split_string;

    int i = 0;
    while (i < input.size())
    {
        int num_rooms = std::stoi(input[i]);
        i++;

        std::vector<std::pair<int, std::vector<int>>> rooms;
        int temp = i;
        for (; i < temp + num_rooms; i++)
        {
            split_string = split(input[i], ' ');
            int energy_level = std::stoi(split_string[0]);
            int num_neighbours = std::stoi(split_string[1]);
            std::vector<int> neighbours;
            int num_rooms_scanned = 0;

            for (int k = 2; k < split_string.size(); k++)
            {
                neighbours.emplace_back(std::stoi(split_string[k]) - 1);
                num_rooms_scanned++;
            }

            while (num_rooms_scanned < num_neighbours)
            {
                i++;
                num_rooms++;
                split_string = split(input[i], ' ');
                for (int k = 0; k < split_string.size(); k++)
                {
                    neighbours.emplace_back(std::stoi(split_string[k]) - 1);
                    num_rooms_scanned++;
                }
            }
            rooms.emplace_back(energy_level, neighbours);
        }
        output.emplace_back(rooms);
    }
    return output;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output = "";

    for (const bool &sub_solution : solution)
    {
        if (sub_solution)
        {
            output += "winnable\n";
        }
        else
        {
            output += "hopeless\n";
        }
    }

    return output;
}

#endif