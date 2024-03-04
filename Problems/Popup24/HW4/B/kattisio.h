#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
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

std::tuple<long long, long long, int> read_input()
{
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> split_string = split(line, ' ');
    long long interval_start = std::stoll(split_string[0]);
    long long interval_end = std::stoll(split_string[1]);
    int cross_sum = std::stoi(split_string[2]);

    return std::tuple{interval_start, interval_end, cross_sum};
}

#endif