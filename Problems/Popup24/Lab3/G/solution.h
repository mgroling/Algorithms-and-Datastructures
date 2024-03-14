// Authors: Marc Gröling

#include "prime_sieve.h"

#include <vector>

std::pair<int, std::vector<bool>> solve_problem(const std::pair<int, std::vector<int>> input)
{
    Prime_Sieve ps = Prime_Sieve(input.first);
    std::vector<bool> query_answers;

    for (const int &query : input.second)
    {
        query_answers.emplace_back(ps.is_prime(query));
    }

    return {ps.get_num_primes(), query_answers};
}