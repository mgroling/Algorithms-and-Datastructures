#include "kattisio.h"
#include "solution.h"

int main()
{
    // std::pair<std::vector<Point<long double>>, std::vector<Point<long double>>> problem = parse_input(read_input());
    // long double solution = solve_problem(problem);
    // std::cout << format_output(solution);

    std::vector<std::pair<Point<long double>, bool>> anchor_points = {{Point<long double>(6, 25), true}};
    Point<long double> toy(0, 0);
    Point<long double> last_toy(15, 5);
    std::vector<Point<long double>> trees{Point<long double>(7, 4), Point<long double>(9, 11), Point<long double>(4, 9),
                                          Point<long double>(1, 19)};
    double max_distance = 0;
    double distance_to_anchor = 0;
    insert_wrapped_trees(toy, last_toy, anchor_points, trees, max_distance, distance_to_anchor);

    return 0;
}
