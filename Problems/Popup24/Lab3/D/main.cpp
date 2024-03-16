// Authors: Marc Gröling

#include "kattisio.h"
#include "solution.h"

int main()
{
    // std::vector<Test_case> problem = parse_input(read_input());
    // std::vector<unsigned long long> solution = solve_problem(problem);
    // std::cout << format_output(solution);

    unsigned long long num1 = 1e17;
    unsigned long long num2 = 1.11e2;
    unsigned long long modulus = 1e18;
    std::cout << modulo_multiply(num1, num2, modulus) << "\n";

    return 0;
}
