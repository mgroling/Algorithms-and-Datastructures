#include "kattisio.h"
#include "solution.h"

int main()
{
    // std::pair<std::vector<Point<int>>, std::vector<Point<int>>> problem = parse_input(read_input());
    // double solution = solve_problem(problem);
    // std::cout << format_output(solution);

    std::vector<std::pair<Point<int>, bool>> anchor_points = {{Point(6, 25), true}};
    Point<int> toy(0, 0);
    Point<int> last_toy(15, 5);
    std::vector<Point<int>> trees{Point(7, 4), Point(9, 11), Point(4, 9), Point(1, 19)};
    double max_distance = 0;
    double distance_to_anchor = 0;
    insert_wrapped_trees(toy, last_toy, anchor_points, trees, max_distance, distance_to_anchor);

    return 0;
}
