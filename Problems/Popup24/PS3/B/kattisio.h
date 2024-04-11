#ifndef kattisio
#define kattisio

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

struct Test_case
{
    std::vector<std::string> sentence;
    std::unordered_map<std::string, int> word_repetitions;
    std::unordered_map<std::string, std::pair<int, std::string>> all_translations;
    std::unordered_map<std::string, std::pair<int, std::string>> correct_translations;
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

    for (int i = 0; i < 3; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    int num_translations = std::stoi(line);

    for (int i = 0; i < num_translations; i++)
    {
        std::getline(std::cin, line);
        output.push_back(line);
    }

    return output;
}

Test_case parse_input(const std::vector<std::string> &input)
{
    std::vector<std::string> split_string;
    std::vector<std::string> sentence = split(input[1], ' ');
    std::unordered_map<std::string, int> word_repetitions;
    for (const std::string &word : sentence)
    {
        auto ptr = word_repetitions.find(word);
        if (ptr != word_repetitions.end())
        {
            ptr->second++;
        }
        else
        {
            word_repetitions[word] = 1;
        }
    }

    std::unordered_map<std::string, std::pair<int, std::string>> all_translations;
    std::unordered_map<std::string, std::pair<int, std::string>> correct_translations;
    for (int i = 3; i < input.size(); i++)
    {
        split_string = split(input[i], ' ');

        auto ptr_temp = word_repetitions.find(split_string[0]);
        if (ptr_temp != word_repetitions.end())
        {
            auto ptr = all_translations.find(split_string[0]);
            if (ptr != all_translations.end())
            {
                ptr->second.first++;
                ptr->second.second = split_string[1];
            }
            else
            {
                all_translations[split_string[0]] = {1, split_string[1]};
            }

            if (split_string[2] == "correct")
            {
                ptr = correct_translations.find(split_string[0]);
                if (ptr != correct_translations.end())
                {
                    ptr->second.first++;
                    ptr->second.second = split_string[1];
                }
                else
                {
                    correct_translations[split_string[0]] = {1, split_string[1]};
                }
            }
        }
    }

    return Test_case{sentence, word_repetitions, all_translations, correct_translations};
}

std::string format_output(const std::vector<std::string> &solution)
{
    std::string output = "";

    for (const std::string &sub_solution : solution)
    {
        output += sub_solution + '\n';
    }

    return output;
}

#endif