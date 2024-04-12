/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

WFF ’N PROOF is a logic game played with dice. Each die has six faces representing some subset of the possible symbols
K, A, N, C, E, p, q, r, s, t. A Well-formed formula (WFF) is any string of these symbols obeying the following rules:

    -p, q, r, s, and t are WFFs

    -if w is a WFF, Nw is a WFF

    -if w and x are WFFs, Kwx, Awx, Cwx, and Ewx are WFFs.

The meaning of a WFF is defined as follows:

    -p, q, r, s, and t are logical variables that may take on the value 0 (false) or 1 (true).

    -K, A, N, C, E mean and, or, not, implies, and equals as defined in the truth table below.

w       x       Kwx     Awx     Nw      Cwx     Ewx
1       1       0       1       0       0       0
1       0       0       1       0       0       0
0       1       0       1       1       1       0
0       0       0       0       1       1       1

A tautology is a WFF that has value 1 (true) regardless of the values of its variables. For example, ApNp is a tautology
because it is true regardless of the value of p. On the other hand, ApNq is not, because it has the value 0 for p = 0, q
= 1.

You must determine whether or not a WFF is a tautology.

----------------------------------------------------- INPUT -----------------------------------------------------

Input consists of several test cases. Each test case is a single line containing a WFF with no more than 100 symbols. A
line containing 0 follows the last case.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output a line containing “tautology” or “not” as appropriate.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
ApNp
ApNq
0

Sample Output:
tautology
not

----------------------------------------------------- SOLUTION -----------------------------------------------------

Since there are only 5 variables, one can easily go through the 2^5 = 32 combinations to determine whether or not a WFF
is true for all combinations. The real "challenge" in this problem seems to be to parse the statement efficiently.

Parsing the statement can be done with a stack, we push symbols onto the stack and in certain conditions, we can pop the
stack again:

- if the top 2 elements on the stack are a boolean value (so a variable or a previously evaluated statement)
- if

*/

#include <stack>
#include <string>
#include <vector>

bool solve_test_case(const std::string &test_case)
{
}

std::vector<bool> solve_problem(const std::vector<std::string> &test_cases)
{
    std::vector<bool> output;

    for (const std::string &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}