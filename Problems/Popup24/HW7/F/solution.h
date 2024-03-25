/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

It has been a long day at your new job. You have spent all day optimizing the most important Suffix-Array data
structures your new employer, the GCPC ([G]lobal Suffix [C]ollecting and [P]rocessing [C]ollective), works with. The
moment you were just about to shut down your workstation you stop and stare at the monitor. Your test run just has
revealed that large portions of the important data must be corrupted. Sadly, the Company’s backup servers just crashed
yesterday, and now you may have destroyed the valuable Suffix-Arrays.

On inspecting the data, you find that it could hardly be worse. A lot of the suffixes are missing and even the ones
remaining might be broken. You have found examples wherein parts of the letters have been replaced by random letters,
and in some parts you find a single ’*’, the placeholder character you used in the software. This placeholder has
replaced an arbitrarily large substring. Furthermore, you found some inconsistent strings, for which it is not clear
which version of the character is the right one. Your only chance now is to hope and pray that a recovery is possible.

The data is given as a list of suffixes, together with the start-position of the suffix. You also still have a list of
the length of all the data-sets the company has in stock. Can you possibly reconstruct at least the base strings? If so,
one could run one of those fancy new Suffix-Array algorithms to reconstruct the full data-set again.

----------------------------------------------------- INPUT -----------------------------------------------------

The number of test cases t (0 < t <= 100) is given on a single line at the beginning of the input. Every test case is
composed as follows. First, on a single line, the length l of the desired output string is given, together with the
number of (partially broken) suffixes s (1 <= l <= 10 000; 1 <= s <= 10 000). Then s lines follow, giving the position p
(1 <= p <= l) of the suffix in the string and the suffix. The suffix will contain only characters from the set of {a,
..., z,  A, ..., Z, ., *} (the ‘.’ has no special meaning). Each suffix contains at most one ‘*’. The total sum of
characters given for the suffixes will not exceed 500 000.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Whenever it is possible to reconstruct the lost input data print the reconstructed sentence, else print “IMPOSSIBLE” on
a single line. For our case, the recovery is only possible if the set of possible characters for a position in the
string contains exactly one character.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
2
6 6
6 a
5 aa
4 a*a
3 aaaa
2 aaaaa
1 aaaaaa
6 6
6 b
5 aa
4 a*a
3 aaaa
2 aaaaa
1 aaaaaa

Sample Output 1:
aaaaaa
IMPOSSIBLE

----------------------------------------------------- SOLUTION -----------------------------------------------------

Since there is only one '*' character contained in each suffix, we can determine the position of the other characters
(we have to go from the front of the suffix to the star and from the back of the suffix to the star). If any conflicts
between suffixes are encountered, then it is impossible to recover the string. Furthermore, all characters of the string
should be determined by the end.

*/

#include "kattisio.h"

#include <string>
#include <vector>

std::string solve_test_case(const Test_case &test_case)
{
    std::string word(test_case.length_string, static_cast<char>(0));

    for (const std::pair<int, std::string> suffix : test_case.suffixes)
    {
        // go from front to back until a star is encountered
        for (int i = 0; i < suffix.second.size(); i++)
        {
            if (suffix.second[i] != '*')
            {
                int index = i + suffix.first - 1;
                // if the character is assigned and doesn't match the character in the suffix, then we have a conflict
                if (word[index] && suffix.second[i] != word[index])
                {
                    return "IMPOSSIBLE";
                }
                word[index] = suffix.second[i];
            }
            else
            {
                int iteration = 0;
                // go from back to front until the position of the star
                for (int j = suffix.second.size() - 1; j > i; j--)
                {
                    int index = test_case.length_string - 1 - iteration;
                    // if the character is assigned and doesn't match the character in the suffix, then we have a
                    // conflict
                    if (word[index] && suffix.second[j] != word[index])
                    {
                        return "IMPOSSIBLE";
                    }
                    word[index] = suffix.second[j];
                    iteration++;
                }
                break;
            }
        }
    }

    // check that each letter in the word is assigned
    for (const char &letter : word)
    {
        if (!letter)
        {
            return "IMPOSSIBLE";
        }
    }
    return word;
}

std::vector<std::string> solve_problem(const std::vector<Test_case> &test_cases)
{
    std::vector<std::string> output;

    for (const Test_case &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}