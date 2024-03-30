/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

In how many ways can you tile a 3xn rectangle with 2x1 dominoes? (by placing dominoes either horizontally or vertically,
no overlaps)

----------------------------------------------------- INPUT -----------------------------------------------------

Input consists of several test cases followed by a line containing -1. Each test case is a line containing an integer
0 <= n <= 30.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output one integer number giving the number of possible tilings.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
2
8
12
-1

Sample Output 2:
3
153
2131

----------------------------------------------------- SOLUTION -----------------------------------------------------

The main task in this problem is to find the recurrence. One thing to remember is that we only have to consider even n's
(since there are always 0 combinations for tiling a 3xn field with odd n (this can easily be shown by looking at the
area of the field vs the dominoes)).

First, let's define a helper function g(n):

g(n) = number of possible combinations for filing a 3xn field which cannot be cut off anywhere and still be valid (for
each position i in [0, n - 1], there is a horizontal domino that goes from i to i+1)

Looking at examples, it is rather easy to see that g(n) = 3 for n = 2, and g(n) = 2 for all n > 2 (2 | n).

Using g(n) we can find f(n) (which shall denote the number of combinations in general):

f(0) = 1 (for a non-existing field there is exactly one combination)
f(2) = 3
f(n) = g(n) + \sum_{i = 2}^{n - 2} f(i) * g(n - i), for even n
f(n) = 0, for odd n

The intuition here is that the new 3x2 field is either not connected at all, connected with the first 3x2 field next to
it, with the first 3x4 field next to it... etc. (we look at where are cuts in the field (so that both pieces would still
be valid))

*/

#include <vector>

int num_to_index(const int &num)
{
    return (num >> 1) - 1;
}

int index_to_num(const int &index)
{
    return (index << 1) + 2;
}

// g(n)
long long combinations_continous(const long long &n)
{
    return 2 + (n == 2);
}

std::vector<long long> solve_problem(const std::vector<int> &input)
{
    std::vector<long long> combinations;

    int max_n = input[0];
    for (const int &elem : input)
    {
        if (elem > max_n)
        {
            max_n = elem;
        }
    }

    std::vector<long long> dp_vector(max_n / 2);
    // number of combinations for 3x2 is 3
    dp_vector[0] = 3;

    for (int i = 1; i < dp_vector.size(); i++)
    {
        // sum = g(n)
        long long sum = combinations_continous(index_to_num(i));
        for (int j = 0; j < i; j++)
        {
            // sum += f(j) * g(n - j)
            sum += dp_vector[j] * combinations_continous(index_to_num(i) - index_to_num(j));
        }
        dp_vector[i] = sum;
    }

    for (const int &elem : input)
    {
        if (elem == 0)
        {
            combinations.push_back(1);
        }
        else if (elem % 2 == 1)
        {
            combinations.push_back(0);
        }
        else
        {
            combinations.push_back(dp_vector[num_to_index(elem)]);
        }
    }

    return combinations;
}