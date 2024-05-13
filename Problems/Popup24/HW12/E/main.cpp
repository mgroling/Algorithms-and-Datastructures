#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"MARICA", "MARTA", "MATO", "MARA", "MARTINA", "MAT"};
    std::vector<std::string> problem = input;
    uint64_t solution = solve_problem(problem);
    std::cout << format_output(solution);

    return 0;
}
