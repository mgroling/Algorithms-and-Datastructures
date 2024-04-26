/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

The word the is the most common three-letter word. It even shows up inside other words, such as “other” and
“mathematics”. Sometimes it hides, split between two words, such as “not here”. Have you ever wondered what the most
common words of lengths other than three are?

Your task is the following. You will be given a text. In this text, find the most common word of length one. If there
are multiple such words, any one will do. Then count how many times this most common word appears in the text. If it
appears more than once, output how many times it appears. Then repeat the process with words of length 2, 3, and so on,
until you reach such a length that there is no longer any repeated word of that length in the text.

----------------------------------------------------- INPUT -----------------------------------------------------

The input consists of a sequence of lines. The last line of input is empty and should not be processed. Each line of
input other than the last contains at least one but no more than one thousand uppercase letters and spaces. The spaces
are irrelevant and should be ignored.

Note that the last line of the sample input is a blank line.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each line of input, output a sequence of lines, giving the number of repetitions of words of length 1, 2, 3, and so
on. When you reach a length such that there are no repeated words of that length, output one blank line, do not output
anything further for that input line, and move on to the next line of input.

Note that the last line of the sample output is a blank line.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
THE OTHER MATHEMATICS NOT HERE
AA

Sample Output:
5
4
4
2
2
(empty line)
2
(empty line)

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can just brute-force count the number of occurences for each word going from words of length 1 to words of length n.
However, instead of comparing words directly, we use hashes of the words, which can be computed much faster.

*/

#include "hashing.h"

#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> solve_test_case(const std::string &test_case)
{
    std::vector<int> occurences;
    Polynomial_Hash_Family p = Polynomial_Hash_Family(test_case);

    // just brute force it, but instead of comparing words directly use hashes instead
    for (int len = 1; len <= test_case.size(); len++)
    {
        int num_occurences = 0;
        std::unordered_map<uint64_t, int> words;

        for (int start = 0; start < test_case.size() - len + 1; start++)
        {
            uint64_t hash = p.get_hash(start, start + len);
            auto ptr = words.find(hash);
            if (ptr == words.end())
            {
                words[hash] = 1;
            }
            else
            {
                // element found in map => found at least 2 occurences of it, update num_occurences
                ptr->second++;
                if (ptr->second > num_occurences)
                {
                    num_occurences = ptr->second;
                }
            }
        }

        if (num_occurences == 0)
        {
            return occurences;
        }
        occurences.push_back(num_occurences);
    }

    return occurences;
}

std::vector<std::vector<int>> solve_problem(const std::vector<std::string> &test_cases)
{
    std::vector<std::vector<int>> occurences;

    for (const std::string &test_case : test_cases)
    {
        occurences.push_back(solve_test_case(test_case));
    }

    return occurences;
}