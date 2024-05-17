/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Mirko’s great grandmother Katica is an avid mathematician. She likes to torment Mirko with math games. This time she
wrote down a sequence of numbers on a piece of paper and told Mirko he may do the following:

    -Choose any two numbers in the sequence (let’s call them A and B) and a prime number X such that A is divisible by
X. After that, Mirko erases A and writes A/X in its place. In the end he erases B and writes B*x in its place.

Mirko may perform this operation as many times he wants. His goal is to obtain the maximum possible score, because he
gets candy from his great grandmother if he does so. The score for one sequence is the greatest common divisor of all
the numbers in the sequence.

He is not very good at this, and he likes his candy so he has asked you to help him. Write a program that will calculate
the maximum possible score. Since you are such a nice person, you should also print the smallest number of times Mirko
must perform the operation to obtain the maximum possible score.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains one integer N, (1 <= N <= 100), the number of elements in the starting sequence.

The second line of input contains N positive integers smaller than or equal to 1 000 000, the sequence Katica gave to
Mirko.

----------------------------------------------------- OUTPUT -----------------------------------------------------

The one and only line of output should contain two integers. The first integer is the maximal possible score Mirko can
obtain. The second integer is the smallest number of operations Mirko needs to perform to obtain it.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
3
4 4 1

Sample Output 1:
2 1

Sample Input 2:
3
8 24 9

Sample Output 2:
12 3

Sample Input 3:
5
4 5 6 7 8

Sample Output 3:
2 2

----------------------------------------------------- SOLUTION -----------------------------------------------------

The operation described is basically that we can take a prime factor of one number and add it to another.

As such, to get the gcd, we have to check which prime factors we have available and how often. We need them at least n
times to increase the gcd (so divide the number of available ones by n, rounded down). After we have these counts for
each prime factor, we can check how many are missing for each input number, which will be the number of operations
required (since we can only divide by prime numbers).

*/

#include <cmath>
#include <unordered_map>
#include <vector>

// returns an array of tuples with (prime_factor, factorisation count)
std::unordered_map<int, int> find_prime_factors(int number)
{
    std::unordered_map<int, int> prime_factors;

    // check how many 2's are factors in number
    // !(number & 1) is equivalent to number % 2 == 0
    int number_of_2_factors = 0;
    while (!(number & 1))
    {
        number_of_2_factors++;
        number = number >> 1;
    }
    if (number_of_2_factors)
    {
        prime_factors[2] = number_of_2_factors;
    }

    int candidate = 3;
    // search for factors until the number is 1
    while (number != 1)
    {
        int num_factors = 0;
        // divide by the candidate as many times as it is a factor
        while (number % candidate == 0)
        {
            num_factors++;
            number /= candidate;
        }
        // if num_factors > 0, then append it
        if (num_factors)
        {
            prime_factors[candidate] = num_factors;
        }
        candidate++;
    }

    return prime_factors;
}

std::pair<int, int> solve_problem(std::vector<int> &input)
{
    int n = input.size();
    std::vector<std::unordered_map<int, int>> prime_factors;
    prime_factors.reserve(input.size());

    for (const int &num : input)
    {
        prime_factors.emplace_back(find_prime_factors(num));
    }

    std::unordered_map<int, int> prime_factors_total;

    // get the total counts of all prime factors
    for (const std::unordered_map<int, int> &factors : prime_factors)
    {
        for (const std::pair<int, int> &pair : factors)
        {
            auto ptr = prime_factors_total.find(pair.first);
            if (ptr != prime_factors_total.end())
            {
                ptr->second += pair.second;
            }
            else
            {
                prime_factors_total[pair.first] = pair.second;
            }
        }
    }

    std::vector<std::pair<int, int>> factors_used;
    int maximum_obtainable_gcd = 1;
    // check which factors we have for each num, and count how many we have at least n times (or 2n, 3n, etc.)
    for (auto it = prime_factors_total.begin(); it != prime_factors_total.end(); it++)
    {
        it->second /= n;
        if (it->second > 0)
        {
            factors_used.emplace_back(it->first, it->second);
            maximum_obtainable_gcd *= std::pow(it->first, it->second);
        }
    }

    // count how many operations are necessary
    int operations_necessary = 0;
    for (const std::unordered_map<int, int> &factors : prime_factors)
    {
        for (const std::pair<int, int> &used : factors_used)
        {
            auto ptr = factors.find(used.first);
            if (ptr != factors.end())
            {
                operations_necessary += std::max(0, used.second - ptr->second);
            }
            else
            {
                operations_necessary += used.second;
            }
        }
    }

    return {maximum_obtainable_gcd, operations_necessary};
}
