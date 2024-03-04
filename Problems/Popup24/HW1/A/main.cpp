#include "kattisio.h"
#include "solution.h"

#include <iomanip>
#include <limits>

int main()
{
    std::tuple<long double, long double, std::vector<long double>> input = read_input();
    long double solution = solve_problem(std::get<0>(input), std::get<1>(input), std::get<2>(input));
    std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << solution;

    return 0;
}
