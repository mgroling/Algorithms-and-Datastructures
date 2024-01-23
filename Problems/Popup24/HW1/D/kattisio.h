#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

struct Transaction
{
    std::string type;     // possible types are: "buy", "sell", "split", "merge", "die"
    long long num_stocks; // number of stocks used in the transaction
    long long price;      // price of individual stock at time of selling/buying/whatever

    Transaction(const std::string &t, long long num, long long p)
    {
        type = t;
        num_stocks = num;
        price = p;
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
    bool done = line[0] == 'd';
    output.push_back(line);

    while (!done)
    {
        std::getline(std::cin, line);
        done = line[0] == 'd';
        output.push_back(line);
    }
    return output;
}

std::vector<Transaction> parse_input(const std::vector<std::string> &input)
{
    std::vector<Transaction> output;
    for (int i = 0; i < input.size(); i++)
    {
        std::vector<std::string> split_string = split(input[i], ' ');
        if (split_string.size() == 3)
        {
            output.emplace_back(split_string[0], std::stoll(split_string[1]), std::stoll(split_string[2]));
        }
        else
        {
            output.emplace_back(split_string[0], std::stoll(split_string[1]), std::stoll(split_string[1]));
        }
    }
    return output;
}

#endif