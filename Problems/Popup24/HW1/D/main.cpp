#include "kattisio.h"
#include "solution.h"

int main()
{
    // std::vector<Transaction> transactions = parse_input(read_input());
    // double solution = solve_problem(transactions);
    // std::cout << solution << "\n";

    std::vector<std::string> input{"buy 1000 1000", "buy 999 999", "split 497", "merge 727", "die 1000"};
    double output = 1998001;
    std::vector<Transaction> transactions = parse_input(input);
    double solution = solve_problem(transactions);
    std::cout << solution << "\n";

    return 0;
}
