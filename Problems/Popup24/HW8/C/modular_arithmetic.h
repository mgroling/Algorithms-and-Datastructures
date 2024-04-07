// Authors: Marc Gröling
// all functions assume that the inputs are 0 <= num < modulus (except the one to compute linear recurrences)

#ifndef modular_arithmetic
#define modular_arithmetic

#include <cassert>
#include <tuple>
#include <type_traits>
#include <vector>

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
    T r = (num1 * num2 - c * modulus) % modulus;
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

// computes the solution (if it exists) of x that fulfills:
// (1) x % n1 = a1 % n1
// (2) x % n2 = a2 % n2
// returns (bool, x, modulus), bool tells if there is a solution
// if there is a solution, then 0 <= x < modulus (modulus = lcm(n1, n2))
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
        // x = a1 * v * n2 + a2 * u * n1
        // is a solution because:
        // x (mod n1) = a1 * v * n2 + a2 * u * n1 = a1 * (1 - u * n1) + a2 * u * n1
        // = a1 + (a2 - a1) * u * n1 (of which the second part is = 0, since n1 is a factor)
        // => x = a (mod n1), analogous for x = a2 (mod n2)
        return {true,
                modulo_add(modulo_multiply(modulo_multiply(a1, v, modulus), n2, modulus),
                           modulo_multiply(modulo_multiply(a2, u, modulus), n1, modulus), modulus),
                modulus};
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

// perhaps using arrays (instead of vectors) for this class would be better but then I would have to use templates for
// all functions that use it, which I don't want to (in practice one would use a library for this anyway)
template <typename T> class ModuloMatrix
{
  public:
    ModuloMatrix(const int &num_rows, const int &num_cols, const T &modulus)
    {
        static_assert(std::is_signed<T>::value, "T must be a signed integer type");
        this->matrix = std::vector<T>{};
        this->matrix.resize(num_rows * num_cols);
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        this->modulus = modulus;
    }

    ModuloMatrix(const std::vector<T> &matrix, const int &num_rows, const int &num_cols, const T &modulus)
    {
        static_assert(std::is_signed<T>::value, "T must be a signed integer type");

        this->matrix = matrix;
        this->modulus = modulus;
        this->num_rows = num_rows;
        this->num_cols = num_cols;
    }

    ModuloMatrix(const std::vector<std::vector<T>> &matrix, const T &modulus)
    {
        static_assert(std::is_signed<T>::value, "T must be a signed integer type");

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                this->matrix.push_back(matrix[i][j]);
            }
        }
        this->modulus = modulus;
        this->num_rows = matrix.size();
        this->num_cols = matrix[0].size();
    }

    T get(const int &row, const int &col)
    {
        return matrix[row * num_cols + col];
    }

    ModuloMatrix operator+(const ModuloMatrix &other)
    {
        // check that dimensions align
        assert(num_rows == other.num_rows && num_cols == other.num_cols);
        // check that modulus of both matrices is the same
        assert(modulus == other.modulus);

        ModuloMatrix result = ModuloMatrix<T>(num_rows, num_cols, modulus);
        for (int i = 0; i < matrix.size(); i++)
        {
            result.matrix[i] = modulo_add(matrix[i], other.matrix[i], modulus);
        }

        return result;
    }

    ModuloMatrix operator*(const ModuloMatrix &other)
    {
        // check that dimensions align
        assert(num_cols == other.num_rows);
        assert(modulus == other.modulus);

        ModuloMatrix result = ModuloMatrix<T>(num_rows, num_cols, modulus);
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < other.num_cols; j++)
            {
                T sum = 0;
                for (int k = 0; k < num_cols; k++)
                {
                    sum = modulo_add(
                        sum, modulo_multiply(matrix[i * num_cols + k], other.matrix[k * other.num_cols + j], modulus),
                        modulus);
                }
                result.matrix[i * num_cols + j] = sum;
            }
        }
        return result;
    }

    ModuloMatrix power(long long power)
    {
        // check that matrix is quadratic
        assert(num_rows == num_cols);

        // identity matrix
        ModuloMatrix result = ModuloMatrix(num_rows, num_cols, modulus);
        for (int i = 0; i < num_rows; i++)
        {
            result.matrix[i * num_cols + i] = 1;
        }

        ModuloMatrix temp = ModuloMatrix(matrix, num_rows, num_cols, modulus);
        while (power > 0)
        {
            if (power & 1)
            {
                result = result * temp;
            }
            power = power >> 1;
            temp = temp * temp;
        }

        return result;
    }

  private:
    std::vector<T> matrix;
    T modulus;
    int num_rows;
    int num_cols;
};

long long compute_linear_recurrence_modulo(const std::vector<long long> &coefficients,
                                           const std::vector<long long> &initial_values, const long long &n,
                                           const long long &modulus)
{
    if (n < initial_values.size())
    {
        return initial_values[n] % modulus;
    }

    // initialize matrix A that looks like this (for 5 coefficients):
    // 1     0     0     0     0
    // a_0   a_1   a_2   a_3   a_4
    // 0     1     0     0     0
    // 0     0     1     0     0
    // 0     0     0     1     0
    std::vector<std::vector<long long>> matrix_values_A(coefficients.size(),
                                                        std::vector<long long>(coefficients.size(), 0));
    matrix_values_A[0][0] = 1;
    for (int i = 0; i < coefficients.size(); i++)
    {
        matrix_values_A[1][i] = coefficients[i];
        if (i >= 2)
        {
            matrix_values_A[i][i - 1] = 1;
        }
    }
    ModuloMatrix A = ModuloMatrix(matrix_values_A, modulus);

    // and the vector x_t:
    // 1
    // f(t)
    // f(t - 1)
    // f(t - 2)
    // f(t - 3)
    std::vector<std::vector<long long>> matrix_values_x_t(coefficients.size(), std::vector<long long>(1, 0));
    matrix_values_x_t[0][0] = 1;
    for (int i = 0; i < initial_values.size(); i++)
    {
        matrix_values_x_t[initial_values.size() - i][0] = initial_values[i];
    }
    ModuloMatrix x_t = ModuloMatrix(matrix_values_x_t, modulus);

    // now compute A^e * x_t = x_(t + e)
    ModuloMatrix result = A.power(n - initial_values.size() + 1) * x_t;

    // and finally return f(n)
    return result.get(1, 0);
}

#endif