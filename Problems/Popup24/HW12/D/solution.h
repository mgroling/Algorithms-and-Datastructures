/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Given a positive integer, N , the sequence of all fractions a/b with 0 <= a <= b, 1 <= b <= N and a and b relatively
prime, listed in increasing order, is called the Farey Sequence of order N. For example, the Farey Sequence of order 6
is:

0/1, 1/6, 1/5, 1/4, 1/3, 2/5, 1/2, 3/5, 2/3, 3/4, 4/5, 5/6, 1/1

For this problem, you will write a program to compute the length of the Farey Sequence of order N.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains a single integer P (1 <= P <= 10 000), which is the number of data sets that follow.
Each data set should be processed identically and independently.

Each data set consists of a single line of input. It contains the data set number, K, followed by the order N (2 <= N <=
10 000) of the Farey Sequence whose length is to be found.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each data set there is a single line of output. The single output line consists of the data set number, K, followed
by a single space followed by the length of the Farey Sequence as a decimal integer.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
4
1 6
2 15
3 57
4 9999

Sample Output:
1 13
2 73
3 1001
4 30393487

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can simply use the formula of the farey sequence. This problem is about not recomputing it everything all the time,
so we just save the value of euler's totient function (which is used for computing the farey sequence) for 1 <= i <=
max(N).

*/

#include <vector>

// returns an array containing the prime factors of a number
std::vector<int> find_prime_factors(int number)
{
    std::vector<int> prime_factors;

    // check how many 2's are factors in number
    // !(number & 1) is equivalent to number % 2 == 0
    bool any_2_factors = false;
    while (!(number & 1))
    {
        any_2_factors = true;
        number = number >> 1;
    }
    if (any_2_factors)
    {
        prime_factors.push_back(2);
    }

    int candidate = 3;
    // search for factors until the number is 1
    while (number != 1)
    {
        bool any_candidate_factors = false;
        // divide by the candidate as many times as it is a factor
        while (number % candidate == 0)
        {
            any_candidate_factors = true;
            number /= candidate;
        }
        if (any_candidate_factors)
        {
            prime_factors.push_back(candidate);
        }
        // only need to consider odd candidates (or really just prime numbers (which may be precomputed), but this is
        // easier and fast enough)
        candidate += 2;
    }

    return prime_factors;
}

int eulers_totient_function(const int &n)
{
    std::vector<int> prime_factors = find_prime_factors(n);
    double product = n;
    for (const int &prime_factor : prime_factors)
    {
        product *= (1.0 - (1.0 / prime_factor));
    }
    return product;
}

std::vector<int> solve_problem(const std::pair<int, std::vector<int>> &input)
{
    const int &max_n = input.first;
    const std::vector<int> &data_sets = input.second;

    // compute euler's totient function for 1..max_n
    std::vector<int> eulers_totient(max_n);
    for (int i = 0; i < max_n; i++)
    {
        eulers_totient[i] = eulers_totient_function(i + 1);
    }

    std::vector<int> output;
    output.reserve(data_sets.size());
    for (const int &n : data_sets)
    {
        int sum = 1;
        for (int i = 0; i < n; i++)
        {
            sum += eulers_totient[i];
        }
        output.push_back(sum);
    }

    return output;
}