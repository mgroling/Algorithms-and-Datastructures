#include "prime_sieve.h"

#include <cmath>
#include <vector>

std::pair<int, int> solve_test_case(const int &num)
{
    if (num == 1)
    {
        return {num, 0};
    }

    Prime_Sieve p = Prime_Sieve(num / 4);
    int count = 0;

    int num_perfect_squares = 0;
    for (int i = 5; i < num; i += 4)
    {
        if (p.is_prime(i))
        {
            int temp = num / i;

            if (temp < 5)
            {
                break;
            }
            count += p.get_num_primes(temp);
            if (p.is_prime(i) && i * i <= num)
            {
                num_perfect_squares++;
            }
        }
    }

    return {num, (count + num_perfect_squares) / 2};
}

std::vector<std::pair<int, int>> solve_problem(const std::vector<int> &test_cases)
{
    std::vector<std::pair<int, int>> output;

    for (const int &test_case : test_cases)
    {
        output.push_back(solve_test_case(test_case));
    }

    return output;
}