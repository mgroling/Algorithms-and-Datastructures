#include "geometry.h"
#include "kattisio.h"

#include <cmath>
#include <tuple>
#include <vector>

Point<double> rotate_point(const Point<double> &p, const Point<double> &center)
{
}

Point<double> get_third_vertex(const double &a, const double &b, const double &c)
{
    double a_squared = std::pow(a, 2);
    double b_squared = std::pow(b, 2);
    double c_squared = std::pow(c, 2);
    double x = (c_squared + a_squared - b_squared) / (2 * a);
    double y = std::sqrt(c_squared - std::pow(x, 2));
    return Point<double>(x, y);
}

double get_triangle_length(const int &a, const int &b, const int &c)
{
    // create a triangle with the given side lengths
    std::vector<Point<double>> vertices{Point<double>(0, 0), Point<double>(0, a), get_third_vertex(a, b, c)};

    // compute the center of the triangle
    Point<double> center;
    for (const Point<double> &p : vertices)
    {
        center = center + p;
    }

    // given the triangle construction that we used, p2 has the side lengths a and b next to it
    Point<double> vector_from_center_to_rope = (vertices[1] - center).normalized();
    Point<double> vector_positive_yaxis = Point<double>(0, 1);

    // get the angle between the two
    double angle = vector_positive_yaxis.angle(vector_from_center_to_rope);

    // rotate the coordinates by the angle to get the position of how the triangle would hang
    return 0;
}

double solve_problem(std::vector<std::tuple<int, int, int>> &input)
{
    double required_length = 0;

    for (const std::tuple<int, int, int> &side_lengths : input)
    {
        required_length +=
            get_triangle_length(std::get<0>(side_lengths), std::get<1>(side_lengths), std::get<2>(side_lengths));
    }

    return required_length;
}