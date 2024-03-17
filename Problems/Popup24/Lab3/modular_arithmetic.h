// Authors: Marc Gröling

#ifndef modular_arithmetic
#define modular_arithmetic

unsigned long long modulo_add(const unsigned long long &num1, const unsigned long long &num2,
                              const unsigned long long &modulus)
{
    return (num1 + num2) % modulus;
}

unsigned long long modulo_subtract(const unsigned long long &num1, const unsigned long long &num2,
                                   const unsigned long long &modulus)
{
    return (num1 + modulus - num2) % modulus;
}

unsigned long long modulo_multiply(unsigned long long num1, unsigned long long num2, const unsigned long long &modulus)
{
    num1 %= modulus;
    num2 %= modulus;
    long double x = num1;
    // keeps the msb of the result of num1 * num2 % modulus (with the below line)
    unsigned long long c = x * num2 / modulus;
    // first multiplication keeps the lsb of the result and the second the msb of the result (I think, not sure tbh)
    long long r = (long long)(num1 * num2 - c * modulus) % modulus;
    return r < 0 ? r + modulus : r;
}

unsigned long long modulo_power(unsigned long long num, unsigned long long power, const unsigned long long &modulus)
{
    unsigned long long result = !(modulus == 1);
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
unsigned long long extended_gcd(unsigned long long a, unsigned long long b, long long &x, long long &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    unsigned long long gcd = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// implements 1 / num % modulus
// returns a pair with true/false (depending on if the inverse exists), and the result
std::pair<bool, unsigned long long> modulo_inverse(const unsigned long long &num, const unsigned long long &modulus)
{
    long long x, y;
    // unsigned long long gcd = std::gcd(num, modulus);
    unsigned long long gcd = extended_gcd(num, modulus, x, y);
    if (gcd != 1)
    {
        return {false, 0};
    }
    // num and modulus are relatively prime => inverse exists and is num^(modulus-2) % modulus
    // return {true, modulo_power(num, modulus - 2, modulus)};
    return {true, (x + modulus) % modulus};
}

// implements: num1 / num2 % modulus
// returns a pair with true/false (depending on if an inverse of num2 exists), and the result
std::pair<bool, unsigned long long> modulo_divide(const unsigned long long &num1, const unsigned long long &num2,
                                                  const unsigned long long &modulus)
{
    std::pair<bool, unsigned long long> inverse = modulo_inverse(num2, modulus);
    if (inverse.first)
    {
        return {true, modulo_multiply(num1, inverse.second, modulus)};
    }
    return {false, 0};
}

#endif