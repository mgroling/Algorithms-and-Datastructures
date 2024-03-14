// Authors: Marc Gröling
// small reminder: num << 1 === num * 2, num >> 1 === num / 2

#include <cmath>
#include <vector>

// Datastructure that can answer if a number is prime in O(1) time
// The construction takes O(n log_2(log_2(n))) time
// And the datastructure requires ~n/2 space (only stores odd numbers)
class Prime_Sieve
{
  public:
    Prime_Sieve(const int &max_num)
    {
        int size_vector = (max_num >> 1) - (max_num % 2 == 0);
        prime_vector = std::vector<bool>(size_vector, true);
        num_primes = 1;
        int sqrt_max = std::ceil(std::sqrt(max_num));

        // only need to loop to sqrt(max_num), since C = A * B (one of A or B must be <= sqrt(C))
        for (int i = 0; i < sqrt_max; i++)
        {
            int candidate = indexToPrime(i);
            if (prime_vector[i])
            {
                int candidate_times_two = candidate * 2;
                // can only consider the cases of candidate multiplied by an odd number
                for (int j = candidate_times_two + candidate; j <= max_num; j += candidate_times_two)
                {
                    prime_vector[primeToIndex(j)] = false;
                }
            }
        }

        for (int i = 0; i < size_vector; i++)
        {
            num_primes += prime_vector[i];
        }
    }

    // returns whether or not a number is prime
    // assumes 1 <= num <= max_num
    bool is_prime(int num)
    {
        if (num == 2)
        {
            return true;
        }
        if (num == 1 || (num != 2 && num % 2 == 0))
        {
            return false;
        }
        return prime_vector[primeToIndex(num)];
    }

    // returns the number of primes in {1, 2, 3, ..., max_num}
    int get_num_primes()
    {
        return num_primes;
    }

  private:
    // only stores for odd numbers starting at 3
    std::vector<bool> prime_vector;
    int num_primes;

    int indexToPrime(const int &index)
    {
        return ((index + 1) << 1) + 1;
    }

    int primeToIndex(const int &prime_index)
    {
        return ((prime_index - 1) >> 1) - 1;
    }
};