/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Note that this is a harder version of the problem anti11.

Danny Ocean likes many things: casinos, elaborate heists, and complicated romantic relationships. But it’s a
little-known fact that Danny loves binary strings most of all — binary strings of any length and composition. One day,
however, he suddenly develops a mysterious allergy to all binary strings containing the substring 11. This strange
illness lasts exactly one week, during which time he has to work very hard to avoid any such “contaminated” binary
strings. At the end of the week, the allergy vanishes as unexpectedly as it appeared, and for a brief moment Danny is
elated that all binary strings are again available for him to enjoy. Alas, this hope is short lived, for no sooner has
the first allergy disappeared than it is replaced by anther, this time to all binary strings containing the substring
10101. The second allergy also lasts exactly one week, after which it is replaced by yet another, and another, and so
on, one per week, ad infinitum.

Danny has (mostly) adjusted to his allergic affliction, and is optimistic that there are still plenty of binary strings
for him to enjoy each week, but he’s not sure exactly how many, so he has hired you to write a program to find out.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains a single integer T (1 <= T <= 100) representing the number of test cases. This is
followed by lines, each of which contains a single integer n (1 <= n <= 10 000) followed by a non-empty string b
consisting only of the characters 0 and 1. The length of b is at most 10.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output consists of T lines, one per case. The output for a given case is the number of binary strings of length n that
do not contain b as a substring. Since these values can be quite large, output each value mod (10^9 + 7).

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
3
1 0
3 101
5 11

Sample Output:
1
7
13

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problem can be solved efficiently using recursion. It's probably easiest explained with an example:

x = 1101

a(n) := the number of bitstrings of size n that don't contain x and end with 0
b(n) := the number of bitstrings of size n that don't contain x and end with 1
c(n) := the number of bitstrings of size n that don't contain x and end with 00
d(n) := the number of bitstrings of size n that don't contain x and end with 010
e(n) := the number of bitstrings of size n that don't contain x and end with 01

Notice that the sum of these two will be the solution for this problem. Now calculate how the recursions work for these:

a(n) = a(n-1) + b(n-1), since these strings of size n-1 didn't contain x, the only way they could contain it is if the
last 0 will be used for it. However, since x ends with a 1 this can't be the case.
b(n) = b(n-1) + c(n-1) + d(n-1), since the last bit of x is a 1, there might be an x that could be created if we just
sum over a(n-1) and b(n-1). This is why we need to make sure that there is a difference and sum over all. (difference in
the first character before => 1, difference in the second character before => 00, difference in the third character
before => 010)
c(n) = a(n-1), since 00 != x[2:]
d(n) = e(n-1), since 010 != x[1:]
e(n) = c(n-1) + d(n-1), since 01 == x[2:] we need to sum over the variations as done with b(n)

*/

#include "modular_arithmetic.h"

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

char flip_char(const char &character)
{
    if (character == '0')
    {
        return '1';
    }
    return '0';
}

long long solve_test_case(std::pair<int, std::string> test_case)
{
    std::string bitstring = test_case.second;
    // trivial cases
    if (bitstring.size() == 1)
    {
        return 1;
    }
    if (test_case.first < bitstring.size())
    {
        return 1 << test_case.first;
    }
    if (test_case.first == bitstring.size())
    {
        return (1 << test_case.first) - 1;
    }

    // 10^9 + 7
    long long modulus = 1000000007LL;

    std::unordered_map<std::string, int> end_string_map = {{"0", 0}, {"1", 1}};
    int num_strings = 2;
    std::vector<std::vector<int>> recursion_formulas;
    // add recursion of variations
    if (bitstring.back() == '0')
    {
        std::vector<int> recursion_formula_0 = {bitstring[bitstring.size() - 2] == '0' ? 1 : 0};
        for (int i = 2; i < bitstring.size(); i++)
        {
            recursion_formula_0.emplace_back(i);
        }
        std::vector<int> recursion_formula_1 = {0, 1};
        recursion_formulas.push_back(recursion_formula_0);
        recursion_formulas.push_back(recursion_formula_1);
    }
    else
    {
        std::vector<int> recursion_formula_0 = {0, 1};
        std::vector<int> recursion_formula_1 = {bitstring[bitstring.size() - 2] == '0' ? 1 : 0};
        for (int i = 2; i < bitstring.size(); i++)
        {
            recursion_formula_1.emplace_back(i);
        }
        recursion_formulas.push_back(recursion_formula_0);
        recursion_formulas.push_back(recursion_formula_1);
    }

    std::queue<std::string> end_strings;
    // insert all strings (the endings of them) into a queue and get the recurrence for them
    for (int i = (int)bitstring.size() - 3; i >= 0; i--)
    {
        std::string substring = bitstring.substr(i, num_strings);
        substring[0] = flip_char(substring[0]);
        end_string_map[substring] = num_strings;
        num_strings++;
        end_strings.push(substring);
    }

    while (!end_strings.empty())
    {
        std::string cur = end_strings.front();
        end_strings.pop();

        std::vector<std::string> recurrences;
        // cur matches the end of the string, so need to sum over the previous variations
        if (bitstring.substr(bitstring.size() - cur.size()) == cur)
        {
            for (int j = 0; j < bitstring.size() - cur.size(); j++)
            {
                recurrences.push_back(flip_char(bitstring[j]) + bitstring.substr(j + 1, bitstring.size() - j - 2));
            }
        }
        else
        {
            recurrences.push_back(cur.substr(0, cur.size() - 1));
        }

        std::vector<int> recursion;
        for (const std::string rec : recurrences)
        {
            auto ptr = end_string_map.find(rec);
            // recurrence for string is already present
            if (ptr != end_string_map.end())
            {
                recursion.push_back(ptr->second);
            }
            else
            {
                // create recurrence for string
                recursion.push_back(num_strings);
                end_string_map[rec] = num_strings;
                num_strings++;
                end_strings.push(rec);
            }
        }
        recursion_formulas.push_back(recursion);
    }

    // 1st row is for m = bitstring.size(), second for m+1 ...
    std::vector<std::vector<long long>> dp_table(test_case.first - bitstring.size() + 1,
                                                 std::vector<long long>(num_strings));
    for (const std::pair<std::string, int> &pair : end_string_map)
    {
        dp_table[0][pair.second] = 1 << (bitstring.size() - pair.first.size());
        // ending of that string aligns with ending of the bitstring => subtract 1 possibility
        if (pair.first == bitstring.substr(bitstring.size() - pair.first.size()))
        {
            dp_table[0][pair.second]--;
        }
    }

    for (int i = 1; i < dp_table.size(); i++)
    {
        // do the recursions for all strings
        for (int j = 0; j < recursion_formulas.size(); j++)
        {
            long long sum = 0;
            for (const int &index : recursion_formulas[j])
            {
                sum = modulo_add(sum, dp_table[i - 1][index], modulus);
            }
            dp_table[i][j] = sum;
        }
    }

    // number of combinations not containing the bit string is the sum of the ones that don't contain it and end with 0
    // or 1
    return modulo_add(dp_table.back()[0], dp_table.back()[1], modulus);
}

std::vector<long long> solve_problem(const std::vector<std::pair<int, std::string>> &problem)
{
    std::vector<long long> output;

    for (const std::pair<int, std::string> &elem : problem)
    {
        output.emplace_back(solve_test_case(elem));
    }

    return output;
}