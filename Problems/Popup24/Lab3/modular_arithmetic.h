// Authors: Marc Gröling

#ifndef modular_arithmetic
#define modular_arithmetic

#include <vector>

unsigned long long modulo_add(const unsigned long long &num1, const unsigned long long &num2,
                              const unsigned long long &modulus)
{
    return (num1 + num2) % modulus;
}

unsigned long long modulo_minus(const unsigned long long &num1, const unsigned long long &num2,
                                const unsigned long long &modulus)
{
    return (num1 + modulus - num2) % modulus;
}

unsigned long long modulo_multiply(const unsigned long long &num1, const unsigned long long &num2,
                                   const unsigned long long &modulus)
{
    long double x = num1;
    unsigned long long c = x * num2 / modulus;
    long long r = (long long)(num1 * num2 - c * modulus) % modulus;
    return r < 0 ? r + modulus : r;
}

unsigned long long modulo_divide(const unsigned long long &num1, const unsigned long long &num2,
                                 const unsigned long long &modulus)
{
}

#endif