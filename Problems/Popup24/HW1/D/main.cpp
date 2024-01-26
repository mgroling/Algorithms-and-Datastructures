#include "kattisio.h"
#include "solution.h"

#include <iomanip>
#include <limits>

int main()
{
    std::vector<Transaction> transactions = parse_input(read_input());
    long double solution = solve_problem(transactions);
    std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << solution << "\n";

    return 0;
}
