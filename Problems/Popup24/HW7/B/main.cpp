#include "kattisio.h"
#include "solution.h"

int main()
{
    std::vector<std::string> input{"10 10",      "HALLOMEINE", "LIEBEWIEGE", "HTESDIRDEN", "NNHEUTEALS",
                                   "OMIRGEHTES", "GANZGUTHEU", "TEUNDICHDE", "NKEDASSEST", "OLLESWETTE",
                                   "RHEUTEISTJ", "1",          "MEINELIEBE"};
    std::pair<std::vector<std::string>, std::vector<std::string>> problem = parse_input(input);
    int solution = solve_problem(problem);
    std::cout << solution << '\n';

    return 0;
}
