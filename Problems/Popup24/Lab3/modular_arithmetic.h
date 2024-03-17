// Authors: Marc Gröling
// T is expected to be an integer type

#ifndef modular_arithmetic
#define modular_arithmetic

template <typename T> T modulo_add(const T &num1, const T &num2, const T &modulus)
{
    return (num1 + num2) % modulus;
}

template <typename T> T modulo_subtract(const T &num1, const T &num2, const T &modulus)
{
    return (num1 + modulus - num2) % modulus;
}

template <typename T> T modulo_multiply(T num1, T num2, const T &modulus)
{
    num1 %= modulus;
    num2 %= modulus;
    long double x = num1;
    // keeps the msb of the result of num1 * num2 % modulus (with the below line)
    T c = x * num2 / modulus;
    // first multiplication keeps the lsb of the result and the second the msb of the result (I think, not sure tbh)
    long long r = (long long)(num1 * num2 - c * modulus) % modulus;
    return r < 0 ? r + modulus : r;
}

template <typename T> T modulo_power(T num, T power, const T &modulus)
{
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
template <typename T> T extended_gcd(T a, T b, long long &x, long long &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    T gcd = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// implements 1 / num % modulus
// returns a pair with true/false (depending on if the inverse exists), and the result
template <typename T> std::pair<bool, T> modulo_inverse(const T &num, const T &modulus)
{
    long long x, y;
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
// returns (x, modulus), such that 0 <= x < modulus
// assumes that n1 and n2 are coprime
template <typename T> std::pair<T, T> chinese_remainder_coprime(const T &a1, const T &a2, const T &n1, const T &n2)
{
    // using chinese remainder formula
    T modulus = n1 * n2;
    // inverses always exist since it is assumed that n1 and n2 are coprime (gcd(n1, n2) = 1)
    T b1 = modulo_inverse(n2, n1).second;
    T b2 = modulo_inverse(n1, n2).second;
    T part1 = modulo_multiply(modulo_multiply(a1, b1, modulus), n2, modulus);
    T part2 = modulo_multiply(modulo_multiply(a2, b2, modulus), n1, modulus);
    return {modulo_add(part1, part2, modulus), modulus};
}

#endif