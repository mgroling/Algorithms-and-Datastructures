/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Samuel W. E. R. Craft is an artist with a growing reputation. Unfortunately, the paintings he sells do not provide him
enough money for his daily expenses plus the new supplies he needs. He had a brilliant idea yesterday when he ran out of
blank canvas: “Why don’t I create a gigantic new painting, made of all the unsellable paintings I have, stitched
together?” After a full day of work, his masterpiece was complete.

That’s when he received an unexpected phone call: a client saw a photograph of one of his paintings and is willing to
buy it now! He had forgotten to tell the art gallery to remove his old works from the catalog! He would usually welcome
a call like this, but how is he going to find his old work in the huge figure in front of him?

Given a black-and-white representation of his original painting and a black-and-white representation of his masterpiece,
can you help S.W.E.R.C. identify in how many locations his painting might be?

----------------------------------------------------- INPUT -----------------------------------------------------

The first line consists of 4 space-separated integers: h_p, w_p, h_m, w_m (1 <= h_p <= h_m, 1 <= w_p <= w_m, 1 <= h_m
<= 2000, 1 <= w_m <= 2000), the height and width of the painting he needs to find, and the height and width of his
masterpiece, respectively.

The next h_p lines have w_p lower-case characters representing his painting. After that, the next h_m lines have w_m
lower-case characters representing his masterpiece. Each character will be either ‘x’ or ‘o’.

----------------------------------------------------- OUTPUT -----------------------------------------------------

A single integer representing the number of possible locations where his painting might be.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
4 4 10 10
oxxo
xoox
xoox
oxxo
xxxxxxoxxo
oxxoooxoox
xooxxxxoox
xooxxxoxxo
oxxoxxxxxx
ooooxxxxxx
xxxoxxoxxo
oooxooxoox
oooxooxoox
xxxoxxoxxo

Sample Output:
4

Explanation:
the painting can be found in the locations (0, 6), (1, 0), (6, 5), (6, 6) where a coordinate (x, y) marks the top-left
corner of the painting at row x and column y.

----------------------------------------------------- SOLUTION -----------------------------------------------------

This problems boils down to defining a hash function that can be recomputed fast when one wants to shift the
portrait-mask to the right and bottom. We use polynomial hash functions here.

Let's say we have a portrait, then each value will be multiplied by b to the power shown here:
15 14 13 12
11 10 9  8
7  6  5  4
3  2  1  0

Now to compute the hash of a mask in the masterpiece fast, we can compute hashes for each column of it (multiplied by b
to the power of):
12
8
4
0

Now if we want to shift the portrait by one to the left, we can multiply everything by b (first step). Then we can get
the hash value of the old column and multiply it by b^4 and subtract that (second step). Finally we can add the new
column (third step):
15 14 13 12       16 15 14 13       15 14 13       15 14 13 12
11 10 9  8   ==>  12 11 10 9   ==>  11 10 9   ==>  11 10 9  8
7  6  5  4   ==>  8  7  6  5   ==>  7  6  5   ==>  7  6  5  4
3  2  1  0        4  3  2  1        3  2  1        3  2  1  0


*/

#include "kattisio.h"

#include <random>
#include <string>
#include <vector>

const uint64_t b = 2;
const uint64_t M = 1465639361006085593ULL;

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

uint64_t compute_hash_initial(const std::vector<std::vector<bool>> &target, const int &start_rows,
                              const int &start_cols, const int &end_rows, const int &end_cols)
{
    uint64_t hash = 0;
    for (int i = start_rows; i < end_rows; i++)
    {
        for (int j = start_cols; j < end_cols; j++)
        {
            hash = modulo_add(modulo_multiply(hash, b, M), (uint64_t)target[i][j], M);
        }
    }

    return hash;
}

void recompute_columns(const std::vector<std::vector<bool>> &painting, std::vector<uint64_t> &columns,
                       const int &old_row, const int &new_row, const uint64_t &b_power_max,
                       const uint64_t &b_power_once)
{
    for (int i = 0; i < painting[0].size(); i++)
    {
        // in each column, remove the top element (located in old_row) and add the new element (located in new_row)
        columns[i] = modulo_add(
            modulo_multiply(modulo_subtract(columns[i], modulo_multiply(painting[old_row][i], b_power_max, M), M),
                            b_power_once, M),
            painting[new_row][i], M);
    }
}

int solve_problem(const Test_case &test_case)
{
    int num_occurences = 0;
    uint64_t target_hash =
        compute_hash_initial(test_case.target, 0, 0, test_case.num_rows_target, test_case.num_cols_target);

    // precompute powers of b for next pre-computation
    uint64_t b_power_col = modulo_power(b, test_case.num_cols_target, M);
    std::vector<uint64_t> b_powers{1};
    b_powers.reserve(test_case.num_rows_target);
    for (int i = 1; i < test_case.num_rows_target; i++)
    {
        b_powers.push_back(modulo_multiply(b_powers.back(), b_power_col, M));
    }

    // precompute hashes of each column (with row length of the target) for fast recomputation of hashes later
    std::vector<uint64_t> hashes_columns(test_case.num_cols, 0);
    for (int i = 0; i < test_case.num_rows_target; i++)
    {
        for (int j = 0; j < test_case.num_cols; j++)
        {
            hashes_columns[j] = modulo_add(
                hashes_columns[j],
                modulo_multiply((uint64_t)test_case.painting[i][j], b_powers[b_powers.size() - i - 1], M), M);
        }
    }

    for (int i = 0; i <= test_case.num_rows - test_case.num_rows_target; i++)
    {
        // compute initial hash of this row by summing up columns
        uint64_t hash = 0;
        for (int j = 0; j < test_case.num_cols_target; j++)
        {
            hash = modulo_add(modulo_multiply(hash, b, M), hashes_columns[j], M);
        }

        for (int j = 0; j <= test_case.num_cols - test_case.num_cols_target; j++)
        {
            // recompute hash
            if (j != 0)
            {
                // multiply hash with b
                hash = modulo_multiply(hash, b, M);
                // subtract old column from hash
                hash = modulo_subtract(hash, modulo_multiply(hashes_columns[j - 1], b_power_col, M), M);
                // add new column to hash
                hash = modulo_add(hash, hashes_columns[j + test_case.num_cols_target - 1], M);
            }

            if (hash == target_hash)
            {
                num_occurences++;
            }
        }

        if (i != test_case.num_rows - test_case.num_rows_target)
        {
            recompute_columns(test_case.painting, hashes_columns, i, i + test_case.num_rows_target, b_powers.back(),
                              b_powers[1]);
        }
    }

    return num_occurences;
}