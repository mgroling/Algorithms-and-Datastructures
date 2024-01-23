/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

MegaFirm Inc. has created a set of patterns to aid its telephone help-desk operators in responding to customers. A
pattern is a phrase consisting of words and placeholders. A word is simply a string of letters. A placeholder is a word
enclosed in angle brackets (that is <...>). A phrase matches a pattern if each placeholder in the pattern can be
systematically replaced by a word so as to make the pattern and phrase equal. By “systematically replaced” we mean that
all placeholders enclosing the same word are replaced by the same word.

For example, the phrase

    to be or not to be

matches the pattern

    <foo> be <bar> not <foo> <baf>

because we can replace <foo> by “to”, <bar> by “or”, and <baf> by “be”.

Given two patterns, you are to find a phrase that matches both.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains an integer 1 <= n <= 100, the number of test cases. Each test case consists of two
lines of input; each a pattern. Patterns consist of lowercase words, and placeholders containing lowercase words. No
pattern exceeds 100 characters. Words contain at most 16 characters. A single space separates adjacent words and
placeholders.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output a phrase that matches both patterns. If several phrases match, any will do, but all words
used in the phrase must obey the same constraints as the words in the input (i.e., they must be lowercase and of length
at most 16). If no phrase matches, output a line containing “-” (a single minus sign).

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
3
how now brown <animal>
<foo> now <color> cow
who are you
<a> <b> <a>
<a> b
c <a>

Sample Output 1:
how now brown cow
-
c b

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can go over both patterns repeatedly, if we find an index where the words of both patterns are non-placeholders, then
we can safely assign a value to a placeholder there, e.g.:
"hello" "<bar>" -> placeholder bar gets value hello
However, when we get the case that we have two placeholders in one index, then we must wait for another rule to
determine the value of either. This is why we repeatedly go over the unassigned words positions. If in the end, we find
that we only have placeholders left, then we can assign any value to both e.g.:
"<bar>" "<foo>" -> can assign an arbitrary value to both placeholders
If at any point, we find a conflict in the two sentences (two words don't match), we return "-" (no solution).

In a way, one can think about this "game" as Sudoku, we need to iteratively assign values to some positions, which will
then help us to determine the value of other positions.
*/

#include "kattisio.h"

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

bool is_placeholder(const std::string &string)
{
    return string[0] == '<';
}

std::vector<std::string> solve_test_case(const Test_case &case1, const Test_case &case2,
                                         std::unordered_map<std::string, std::string> &placeholder_map1,
                                         std::unordered_map<std::string, std::string> &placeholder_map2)
{
    std::vector<std::string> output;
    std::vector<std::string> failure_output{std::string{"-"}};
    std::vector<int> not_assigned_indices;
    Test_case not_solved_cases1;
    Test_case not_solved_cases2;
    for (int i = 0; i < case1.sentence.size(); i++)
    {
        if (is_placeholder(case1.sentence[i]))
        {
            auto pointer = placeholder_map1.find(case1.sentence[i]);
            if (is_placeholder(case2.sentence[i]))
            {
                auto pointer2 = placeholder_map2.find(case2.sentence[i]);
                if (pointer != placeholder_map1.end())
                {
                    if (pointer2 != placeholder_map2.end() && pointer->second != pointer2->second)
                    {
                        return failure_output;
                    }
                    placeholder_map2[case2.sentence[i]] = pointer->second;
                    output.push_back(pointer->second);
                }
                else
                {
                    if (pointer2 != placeholder_map2.end())
                    {
                        placeholder_map1[case1.sentence[i]] = pointer2->second;
                        output.push_back(pointer2->second);
                    }
                    else
                    {
                        output.emplace_back("arbitrary");
                        not_assigned_indices.push_back(i);
                        not_solved_cases1.sentence.push_back(case1.sentence[i]);
                        not_solved_cases2.sentence.push_back(case2.sentence[i]);
                    }
                }
            }
            else
            {
                if (pointer != placeholder_map1.end() && pointer->second != case2.sentence[i])
                {
                    return failure_output;
                }
                placeholder_map1[case1.sentence[i]] = case2.sentence[i];
                output.push_back(case2.sentence[i]);
            }
        }
        else
        {
            if (is_placeholder(case2.sentence[i]))
            {
                auto pointer = placeholder_map2.find(case2.sentence[i]);
                if (pointer != placeholder_map2.end() && pointer->second != case1.sentence[i])
                {
                    return failure_output;
                }
                placeholder_map2[case2.sentence[i]] = case1.sentence[i];
                output.push_back(case1.sentence[i]);
            }
            else
            {
                if (case1.sentence[i] != case2.sentence[i])
                {
                    return failure_output;
                }
                output.push_back(case1.sentence[i]);
            }
        }
    }
    if (not_assigned_indices.size())
    {
        bool all_placeholders_unassigned = true;
        for (int i = 0; i < not_solved_cases1.sentence.size(); i++)
        {
            if (placeholder_map1.find(not_solved_cases1.sentence[i]) != placeholder_map1.end() ||
                placeholder_map2.find(not_solved_cases2.sentence[i]) != placeholder_map2.end())
            {
                all_placeholders_unassigned = false;
                break;
            }
        }

        if (!all_placeholders_unassigned)
        {
            std::vector<std::string> sub_problem =
                solve_test_case(not_solved_cases1, not_solved_cases2, placeholder_map1, placeholder_map2);

            for (int i = 0; i < sub_problem.size(); i++)
            {
                if (sub_problem[i] == "-")
                {
                    return failure_output;
                }
                output[not_assigned_indices[i]] = sub_problem[i];
            }
        }
    }

    return output;
}

std::vector<std::vector<std::string>> solve_problem(std::vector<std::tuple<Test_case, Test_case>> test_cases)
{
    std::vector<std::vector<std::string>> output;
    output.reserve(test_cases.size());

    for (std::tuple<Test_case, Test_case> &tuple_test_case : test_cases)
    {
        std::unordered_map<std::string, std::string> placeholder_map1;
        std::unordered_map<std::string, std::string> placeholder_map2;
        std::vector<std::string> solution = solve_test_case(std::get<0>(tuple_test_case), std::get<1>(tuple_test_case),
                                                            placeholder_map1, placeholder_map2);
        output.push_back(solution);
    }
    return output;
}