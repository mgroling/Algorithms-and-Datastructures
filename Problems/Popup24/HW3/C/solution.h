/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

The ternary expansion of a number is that number written in base 3. A number can have more than one ternary expansion. A
ternary expansion is indicated with a subscript 3. For example, 1 = 1_3 = 0.222.._3, and 0.875 = 0.212121.._3.

The Cantor set is defined as the real numbers between 0 and 1 inclusive that have a ternary expansion that does not
contain a 1. If a number has more than one ternary expansion, it is enough for a single one to not contain a 1.

For example, 0 = 0_3 and 1 = 0.222.._3, so they are in the Cantor set. But 0.875 = 0.212121.._3 and this is its only
ternary expansion, so it is not in the Cantor set.

Your task is to determine whether a given number is in the Cantor set.

----------------------------------------------------- INPUT -----------------------------------------------------

The input consists of several test cases, at most 10.

Each test case consists of a single line containing a number x written in decimal notation, with 0 <= x <= 1, and having
at most 6 digits after the decimal point.

The last line of input is END. This is not a test case.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output MEMBER if x is in the Cantor set, and NON-MEMBER if x is not in the Cantor set.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
0
1
0.875
END

Sample Output:
MEMBER
MEMBER
NON-MEMBER

----------------------------------------------------- SOLUTION -----------------------------------------------------

To solve this, we can compute the ternary expansion of a number. To make sure that we notice repeating patterns, we use
integers to represent the decimals. As such 0.875 would be 875000 and 0.2142 would be 214200 (we can do this, since we
know that none of the test cases will have more than 6 digits after the decimal).

A number has at most 2 ternary expansions. It has exactly 2 if and only if one of the presentations is finite and ends
on a 1. Then we can replace the last one with a 0 and add infintely many 2's.

*/

#include <set>
#include <string>
#include <vector>

constexpr int N = 1000000;

bool solve_test_case(int num)
{
    if (num == N || num == 0)
    {
        return true;
    }

    std::set<int> seen;

    // compute the ternary expansion of num
    while (num)
    {
        seen.insert(num);
        num *= 3;
        int ternary_value = num / N;
        num = num % N;
        if (ternary_value == 1)
        {
            // if this was the last needed digit, then we can also replace this 1 with a 0 and infinitely many 2's
            // following
            return num == 0 ? true : false;
        }
        // we found a repeating pattern
        if (seen.find(num) != seen.end())
        {
            break;
        }
    }

    return true;
}

std::vector<bool> solve_problem(const std::vector<int> &input)
{
    std::vector<bool> output;

    for (const int &num : input)
    {
        output.push_back(solve_test_case(num));
    }

    return output;
}