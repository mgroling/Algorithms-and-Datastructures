#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <vector>

struct Ballot
{
    int num_votes;
    std::vector<int> preferences;

    Ballot(int num_votes_, std::vector<int> preferences_)
    {
        num_votes = num_votes_;
        preferences = preferences_;
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
    int num_ballots = std::stoi(split(line, ' ')[1]);
    output.push_back(line);

    for (int i = 0; i < num_ballots; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

std::vector<Ballot> parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string = split(input[0], ' ');
    int num_candidates = std::stoi(split_string[0]);
    int num_ballots = std::stoi(split_string[1]);

    std::vector<Ballot> ballots;
    ballots.reserve(num_ballots);

    for (int i = 1; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');
        std::vector<int> preferences(num_candidates);
        for (int j = 0; j < split_string[1].size(); j++)
        {
            char c = split_string[1][j];

            preferences[c - 'A'] = j;
        }

        ballots.emplace_back(std::stoi(split_string[0]), preferences);
    }

    return ballots;
}

std::string format_output(const std::vector<bool> &solution)
{
    std::string output;

    for (int i = 0; i < solution.size(); i++)
    {
        output += ('A' + i);
        output += ": ";
        if (solution[i])
        {
            output += "can win\n";
        }
        else
        {
            output += "can't win\n";
        }
    }

    return output;
}

#endif