#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<int> weights = read_input();
    int solution = solve_problem(weights);
    std::cout << solution;

    return 0;
}
