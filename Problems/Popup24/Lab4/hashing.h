#include <random>
#include <string>
#include <vector>

const uint64_t large_primes[] = {1465639361006085593ULL, 1465639361006085569ULL, 1465639361006085439ULL,
                                 1465639361006085437ULL, 1465639361006085427ULL, 1465639361006085413ULL,
                                 1465639361006085407ULL, 1465639361006085301ULL, 1465639361006085229ULL};

uint64_t modulo_add(const uint64_t &num1, const uint64_t &num2, const uint64_t &modulus)
{
    return (num1 + num2) % modulus;
}

uint64_t modulo_subtract(const uint64_t &num1, const uint64_t &num2, const uint64_t &modulus)
{
    return (num1 + modulus - num2) % modulus;
}

uint64_t modulo_multiply(uint64_t num1, uint64_t num2, const uint64_t &modulus)
{
    long double x = num1;
    // keeps the msb of the result of num1 * num2 % modulus (with the below line)
    uint64_t c = x * num2 / modulus;
    // first multiplication keeps the lsb of the result and the second the msb of the result (I think, not sure tbh)
    int64_t r = (int64_t)(num1 * num2 - c * modulus) % (int64_t)modulus;
    return r < 0 ? r + modulus : r;
}

uint64_t modulo_power(uint64_t num, uint64_t power, const uint64_t &modulus)
{
    uint64_t result = !(modulus == 1);
    while (power > 0)
    {
        // look at least significant bit of the power, if it is 1, then mutliply by num^(2^original bit position)
        if (power & 1)
        {
            result = modulo_multiply(result, num, modulus);
        }
        power = power >> 1;
        num = modulo_multiply(num, num, modulus);
    }
    return result;
}

class Polynomial_Hash_Family
{
  public:
    Polynomial_Hash_Family(const std::string &word)
    {
        // choose a random prime number from large_primes
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);
        M = large_primes[dis(gen)];

        // compute hashes for [0, 1), [0, 2), [0, 3), ... [0, n) (index of the word)
        hashes.reserve(word.size());
        uint64_t cur_hash = 0;
        for (const char &letter : word)
        {
            cur_hash = next_hash(cur_hash, letter);
            hashes.push_back(cur_hash);
        }
    }

    // computes the hash of word[start:end] (end is exclusive, notation from Python slicing)
    uint64_t get_hash(const uint64_t &start, const uint64_t &end)
    {
        return modulo_subtract(
            hashes[end - 1], start > 0 ? modulo_multiply(hashes[start - 1], modulo_power(b, end - start, M), M) : 0, M);
    }

  private:
    std::vector<uint64_t> hashes;
    // choose a prime number as M that is close to using 64-bits
    uint64_t M;
    // choose b such that it is greater than any single character for good hash properties
    uint64_t b = 256;

    // hash(word) = word[0] * b^(n-1) + word[1] * b^(n-2) + word[-2] * b + word[-1]
    uint64_t next_hash(const uint64_t &previous_hash, const char &next_letter)
    {
        return modulo_add(modulo_multiply(previous_hash, b, M), (uint64_t)next_letter, M);
    }
};