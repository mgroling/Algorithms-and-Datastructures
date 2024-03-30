// Authors: Marc Gröling
// small reminder: num << 1 === num * 2, num >> 1 === num / 2

#ifndef prime_sieve
#define prime_sieve

#include <cmath>
#include <stdexcept>
#include <vector>

// Datastructure that can answer if a number is prime in O(1) time
// The construction takes O(n log_2(log_2(n))) time
// And the datastructure requires ~n/2 space (only stores odd numbers)
class Prime_Sieve
{
  public:
    // uses Erathostenes' sieve for construction
    Prime_Sieve(const int &max_num)
    {
        if (max_num <= 0)
        {
            throw std::invalid_argument("Invalid argument in Prime_Sieve constructor: Argument " +
                                        std::to_string(max_num) + " must be > 0.");
        }

        max_number = max_num;
        int size_vector = (max_num >> 1) - (max_num % 2 == 0);
        prime_vector = std::vector<bool>(size_vector, true);
        int sqrt_max = std::ceil(std::sqrt(max_num));

        // only need to loop to sqrt(max_num), since C = A * B (one of A or B must be <= sqrt(C))
        int candidate = 3;
        int index = 0;
        while (candidate <= sqrt_max)
        {
            if (prime_vector[index])
            {
                int candidate_times_two = candidate << 1;
                // can start at candidate squared, since numbers before will be checked by previous outer loop iteration
                int candidate_multiplied = candidate * candidate;
                int index_c = number_to_index(candidate_multiplied);

                while (candidate_multiplied <= max_num)
                {
                    prime_vector[index_c] = false;
                    // can only consider candidate multiplied by an odd number
                    candidate_multiplied += candidate_times_two;
                    index_c += candidate;
                }
            }
            // go through odd numbers
            candidate += 2;
            index++;
        }
    }

    // returns whether or not a number in [1, max_num] is prime
    bool is_prime(const int &num)
    {
        if (num < 1 || num > max_number)
        {
            throw std::invalid_argument("Invalid argument in Prime_Sieve.is_prime: Argument " + std::to_string(num) +
                                        " is outside of the allowed range [1, " + std::to_string(max_number) + "].");
        }
        if (num == 2)
        {
            return true;
        }
        if (num == 1 || num % 2 == 0)
        {
            return false;
        }
        return prime_vector[number_to_index(num)];
    }

    // returns the number of primes in [1, max_num]
    int get_num_primes()
    {
        if (max_number == 1)
        {
            return 0;
        }

        int num_primes = 1;

        for (int i = 0; i < prime_vector.size(); i++)
        {
            num_primes += prime_vector[i];
        }

        return num_primes;
    }

  private:
    // only stores for odd numbers starting at 3
    std::vector<bool> prime_vector;
    int max_number;

    int index_to_number(const int &index)
    {
        return ((index + 1) << 1) + 1;
    }

    int number_to_index(const int &prime_index)
    {
        return ((prime_index - 1) >> 1) - 1;
    }
};

std::vector<std::pair<long long, long long>> find_prime_factors(long long number)
{
    std::vector<std::pair<long long, long long>> prime_factors;

    // check how many 2's are factors in number
    // !(number & 1) is equivalent to number % 2 == 0
    long long number_of_2_factors = 0;
    while (!(number & 1))
    {
        number_of_2_factors++;
        number = number >> 1;
    }
    prime_factors.emplace_back(2, number_of_2_factors);

    int candidate = 3;
    // search for factors until the number is 1
    while (number != 1)
    {
        long long num_factors = 0;
        // divide by the candidate as many times as it is a factor
        while (number % candidate == 0)
        {
            num_factors++;
            number /= candidate;
        }
        // if num_factors > 0, then append it
        if (num_factors)
        {
            prime_factors.emplace_back(candidate, num_factors);
        }
        candidate++;
    }

    return prime_factors;
}

#endif