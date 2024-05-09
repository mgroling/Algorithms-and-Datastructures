/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

You have two pictures of an unusual kind of clock. The clock has n hands, each having the same length and no kind of
marking whatsoever. Also, the numbers on the clock are so faded that you can’t even tell anymore what direction is up in
the picture. So the only thing that you see on the pictures, are n shades of the n hands, and nothing else.

You’d like to know if both images might have been taken at exactly the same time of the day, possibly with the camera
rotated at different angles. Task

Given the description of the two images, determine whether it is possible that these two pictures could be showing the
same clock displaying the same time.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line contains a single integer n (2 <= n <= 200 000), the number of hands on the clock.

Each of the next two lines contains n integers a_i (0 <= a_i < 360 000), representing the angles of the hands of the
clock on one of the images, in thousandths of a degree. The first line represents the position of the hands on the first
image, whereas the second line corresponds to the second image. The number a_i denotes the angle between the recorded
position of some hand and the upward direction in the image, measured clockwise. Angles of the same clock are distinct
and are not given in any specific order.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output one line containing one word: possible if the clocks could be showing the same time, impossible otherwise.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
6
1 2 3 4 5 6
7 6 5 4 3 1

Sample Output 1:
impossible

Sample Input 2:
2
0 270000
180000 270000

Sample Output 2:
possible

Sample Input 3:
7
140 130 110 120 125 100 105
235 205 215 220 225 200 240

Sample Output 3:
impossible

----------------------------------------------------- SOLUTION -----------------------------------------------------

First off, sort the hands of the clock by their angle. Now if we can add a number x to one of them (this basically
rotates the picture) such that all hands have equals position, then the pictures could be from the same clock.

Notice that this is equivalent to having the same differences between hands. So now we have a differences array for both
clocks. If we can shift one of them by some number of shifts, then it will equal the other at some point (if they are of
the same picture). However, directly comparing all hand distances would take too long. Instead we compute hashes of the
positions. This saves runtime, as we can cheaply recompute the next hash given a previous hash (of the last shifted
position). A polynomial hash family is used here.

*/

#include <algorithm>
#include <vector>

constexpr uint64_t M = 1465639361006085229ULL;
constexpr uint64_t b = 360000;

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

int distance_hands(const int &hand1_angle, const int &hand2_angle)
{
    if (hand1_angle < hand2_angle)
    {
        return hand2_angle - hand1_angle;
    }
    return 360000 - hand1_angle + hand2_angle;
}

uint64_t initial_hash(const std::vector<int> &numbers)
{
    // hash = numbers[0] * b^(numbers.size() - 1) + numbers[1] * b^(numbers.size()) + ... + numbers[-2] * b +
    // numbers[-1] * b
    uint64_t hash = 0;
    for (const int &num : numbers)
    {
        hash = modulo_add(modulo_multiply(hash, b, M), num, M);
    }

    return hash;
}

uint64_t next_hash(const uint64_t &previous_hash, const uint64_t &b_power, const int &replace)
{
    // hash = prev_hash * b - old_num * b_power + new_num (mod M)
    return modulo_add(modulo_subtract(modulo_multiply(previous_hash, b, M), modulo_multiply(replace, b_power, M), M),
                      replace, M);
}

bool solve_problem(std::pair<std::vector<int>, std::vector<int>> &input)
{
    std::vector<int> &hands1 = input.first;
    std::vector<int> &hands2 = input.second;

    // sort both hands ascendingly
    std::sort(hands1.begin(), hands1.end());
    std::sort(hands2.begin(), hands2.end());

    // go through the sorted lists and compute the distances between ones that are next to each other
    std::vector<int> distances1;
    distances1.reserve(hands1.size());
    std::vector<int> distances2;
    distances2.reserve(hands2.size());

    for (int i = 0; i < hands1.size(); i++)
    {
        distances1.push_back(distance_hands(hands1[i], hands1[(i + 1) % hands1.size()]));
    }
    for (int i = 0; i < hands2.size(); i++)
    {
        distances2.push_back(distance_hands(hands2[i], hands2[(i + 1) % hands2.size()]));
    }

    uint64_t hash1 = initial_hash(distances1);
    uint64_t hash2 = initial_hash(distances2);
    uint64_t b_power = modulo_power(b, distances1.size(), M);
    for (int i = 0; i < distances1.size(); i++)
    {
        if (hash1 == hash2)
        {
            return true;
        }
        hash1 = next_hash(hash1, b_power, distances1[i]);
    }

    return false;
}