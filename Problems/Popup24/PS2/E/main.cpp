#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{
        "4 2", "AA", "AT", "TT", "TC",
    };
    std::vector<std::string> dna_strings = parse_input(read_input());
    std::pair<int, std::vector<std::pair<int, int>>> solution = solve_problem(dna_strings);
    std::cout << format_output(solution) << "\n";

    return 0;
}
