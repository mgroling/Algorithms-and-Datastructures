#ifndef kattisio
#define kattisio

#include <cmath>
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

    while (line != "END")
    {
        output.push_back(line);
        std::getline(std::cin, line);
    }

    return output;
}

std::vector<int> parse_input(const std::vector<std::string> &input)
{
    std::vector<int> output;

    for (const std::string &s : input)
    {
        // strip s of the dot and convert the fractional to an integer (divide by 1e6 to get the original back)
        if (s.size() == 1)
        {
            output.push_back(std::stoi(s) * 1000000);
        }
        else
        {
            std::string temp = s.substr(2);
            output.push_back(std::stoi(temp) * std::pow(10, 6 - temp.size()));
        }
    }

    return output;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output;

    for (const bool &sol : solution)
    {
        output += sol ? "MEMBER\n" : "NON-MEMBER\n";
    }

    return output;
}

#endif