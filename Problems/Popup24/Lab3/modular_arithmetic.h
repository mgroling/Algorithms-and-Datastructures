// Authors: Marc Gröling

#ifndef modular_arithmetic
#define modular_arithmetic

#include <tuple>
#include <type_traits>

template <typename T> T modulo_add(const T &num1, const T &num2, const T &modulus)
{
    static_assert(std::is_integral<T>::value, "T must be an integer type");
    return (num1 + num2) % modulus;
}

template <typename T> T modulo_subtract(const T &num1, const T &num2, const T &modulus)
{
    static_assert(std::is_integral<T>::value, "T must be an integer type");
    return (num1 + modulus - num2) % modulus;
}

// not sure if this function works correctly with custom integer types, only tested with long long
template <typename T> T modulo_multiply(T num1, T num2, const T &modulus)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    num1 %= modulus;
    num2 %= modulus;
    long double x = num1;
    // keeps the msb of the result of num1 * num2 % modulus (with the below line)
    T c = x * num2 / modulus;
    // first multiplication keeps the lsb of the result and the second the msb of the result (I think, not sure tbh)
    T r = (long long)(num1 * num2 - c * modulus) % modulus;
    return r < 0 ? r + modulus : r;
}

template <typename T> T modulo_power(T num, T power, const T &modulus)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    T result = !(modulus == 1);
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

// computes the gcd between a and b and x and y of the form gcd(a, b) = ax + by
// uses the extended euclidean algorithm
template <typename T> T extended_gcd(T a, T b, T &x, T &y)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    T x1, y1;
    T gcd = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// implements 1 / num % modulus
// returns a pair with true/false (depending on if the inverse exists), and the result
template <typename T> std::pair<bool, T> modulo_inverse(const T &num, const T &modulus)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    T x, y;
    T gcd = extended_gcd(num, modulus, x, y);
    if (gcd != 1)
    {
        return {false, 0};
    }
    // num and modulus are relatively prime => inverse exists and is num^(modulus-2) % modulus
    return {true, (x + modulus) % modulus};
}

// implements: num1 / num2 % modulus
// returns a pair with true/false (depending on if an inverse of num2 exists), and the result
template <typename T> std::pair<bool, T> modulo_divide(const T &num1, const T &num2, const T &modulus)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    std::pair<bool, T> inverse = modulo_inverse(num2, modulus);
    if (inverse.first)
    {
        return {true, modulo_multiply(num1, inverse.second, modulus)};
    }
    return {false, 0};
}

// computes the solution of x that fulfills:
// (1) x % n1 = a1 % n1
// (2) x % n2 = a2 % n2
// returns (x, modulus), such that 0 <= x < modulus (modulus = lcm(n1, n2))
template <typename T> std::tuple<bool, T, T> chinese_remainder(const T &a1, const T &a2, const T &n1, const T &n2)
{
    static_assert(std::is_signed<T>::value, "T must be a signed integer type");
    // using chinese remainder formula
    T u, v;
    T gcd = extended_gcd(n1, n2, u, v);
    T modulus = n1 * n2 / gcd;
    // trivial case
    if (a1 == a2)
    {
        return {true, a1 % modulus, modulus};
    }

    if (gcd == 1)
    {
        // inverses exist since gcd(n1, n2) = 1
        T b1 = modulo_inverse(n1, n2).second;
        T b2 = modulo_inverse(n2, n1).second;
        T part1 = modulo_multiply(modulo_multiply(a1, b2, modulus), n2, modulus);
        T part2 = modulo_multiply(modulo_multiply(a2, b1, modulus), n1, modulus);
        // x = a1 * b2 * n2 + a2 * b1 * n1
        // is a solution because:
        // b2 * n2 = 1 (mod n1) (since b2 is the inverse of n2 under n1) => a1 * b2 * n2 = a1 (mod n1)
        // and a2 * b1 * n1 = 0 (mod n1) (since n1 is a factor)
        // => x = a (mod n1), analogous for x = a2 (mod n2)
        return {true, modulo_add(part1, part2, modulus), modulus};
    }

    // a2 - a1 is not divisible by gcd => x doesn't exist
    if (modulo_subtract(a2, a1, gcd) != 0)
    {
        return {false, a1, a2};
    }

    // x = a1 - n1 * u * (a1 - a2) / gcd(n1, n2)
    // is a solution because:
    // (1) x = a1 (mod n1):
    // n1 * u * (a1 - a2) / gcd(n1, n2) (mod n1) = 0 of course (since n1 is a factor), as such x = a1 (mod n1)
    //
    // (2) x = a2 (mod n2)
    // n1 * u = gcd(n1, n2) - n2 * v => x = a1 - n1 * u * (a1 - a2) / gcd(n1, n2) =
    // = a1 - (gcd(n1, n2) - n2 * v) * (a1 - a2) / gcd(n1, n2) =
    // = a1 - ((a1 - a2) - n2 * v * (a1 - a2) / gcd(n1, n2)), n2 * v * (a1 - a2) / gcd(n1, n2) = 0 (n2 is factor)
    // = a1 - a1 + a2 = a2, as such x = a2 (mod n2)
    return {true,
            modulo_subtract(a1, modulo_multiply(modulo_multiply(n1, u, modulus), (a1 - a2) / gcd, modulus), modulus),
            modulus};
}

#endif