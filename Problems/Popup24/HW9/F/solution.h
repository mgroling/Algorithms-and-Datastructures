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

Parsing the statement can be easily achieved with a stack and going from right to left of the string expression. This is
because that for any expression (K, A, N, C, E), all the variables of it are to the right and if we go from right to
left, then once we get to that expression, its arguments are already evaluated.


*/

#include <array>
#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

bool evaluate_expression(const std::string &boolean_expression, const bool &p, const bool &q, const bool &r,
                         const bool &s, const bool &t)
{
    std::stack<bool> variable_stack;
    std::unordered_map<char, bool> variable_map = {{'p', p}, {'q', q}, {'r', r}, {'s', s}, {'t', t}};
    std::unordered_map<char, std::function<bool(bool, bool)>> expression_map;
    expression_map['K'] = [](const bool &a, const bool &b) { return a && b; };
    expression_map['A'] = [](const bool &a, const bool &b) { return a || b; };
    // implies function a => b equivalent to !a || b
    expression_map['C'] = [](const bool &a, const bool &b) { return !a || b; };
    expression_map['E'] = [](const bool &a, const bool &b) { return a == b; };

    // iterate through expression in reverse order
    for (auto it = boolean_expression.rbegin(); it != boolean_expression.rend(); it++)
    {
        auto ptr1 = variable_map.find(*it);
        if (ptr1 != variable_map.end())
        {
            // found a variable (p, q, r, s, t), simply push it onto the stack
            variable_stack.push(ptr1->second);
        }
        else
        {
            auto ptr2 = expression_map.find(*it);
            if (ptr2 != expression_map.end())
            {
                // pop the top 2 elements of the stack, apply the function to it and put the result on the stack again
                bool a = variable_stack.top();
                variable_stack.pop();
                bool b = variable_stack.top();
                variable_stack.pop();
                variable_stack.push(ptr2->second(a, b));
            }
            // symbol is the N-symbol (negation)
            else
            {
                // remove the top element of the stack and replace it with the negated version
                bool a = variable_stack.top();
                variable_stack.pop();
                variable_stack.push(!a);
            }
        }
    }

    return variable_stack.top();
}

bool solve_test_case(const std::string &test_case)
{
    std::array<bool, 2> values{true, false};

    for (const bool &p : values)
    {
        for (const bool &q : values)
        {
            for (const bool &r : values)
            {
                for (const bool &s : values)
                {
                    for (const bool &t : values)
                    {
                        // if the expression is false for any variable combination, then it is not a tautology, so we
                        // can return early
                        if (!evaluate_expression(test_case, p, q, r, s, t))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
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