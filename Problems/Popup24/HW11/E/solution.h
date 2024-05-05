/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

A company makes triangle-shaped ornaments for the upcoming holidays. Each ornament is tied at one of its corners to a
rod using a string of unknown length. Multiple of these ornaments may be attached to the same rod. These ornaments
should be able to swing (rotate around the axis formed by the string) without interfering with each other.

Write a program that computes the minimum required length for the rod, given a list of triangles!

----------------------------------------------------- INPUT -----------------------------------------------------

The input consists of a single test case. The first line contains one integer N (0 < N <= 100), denoting the number of
triangles. The next N lines each contain three integers A, B, C denoting the lengths of the three sides of each
triangle. The triangle will hang from the corner between sides and A and B. You are guaranteed that A, B, C form a
triangle that has an area that is strictly greater than zero.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output the required length L such that all triangles can be hung from the rod, no matter how long or short each
triangle’s string is. No triangle should swing beyond the rod’s ends. You may ignore the thickness of each ornament, the
width of the string and you may assume that the string is attached exactly to the triangle’s end point.

Your answer should be accurate to within an absolute or relative error of 10^-4.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
2
3 3 3
4 4 5

Sample Output 1:
8.0

Sample Input 2:
2
3 3 3
4 5 4

Sample Output 2:
6.843530573929037

Sample Input 3:
3
7 20 14
7 14 20
14 20 7

Sample Output 3:
20.721166413503266

----------------------------------------------------- SOLUTION -----------------------------------------------------

To solve this, we need a function that determines the required width for a single triangle. To do this, we first have to
construct a triangle with the given side lengths. To find out how it would hang, we have to think about how gravity
works. The triangle is hung from one of its corners and then the vector from this corner to the center of the triangle
(i.e. the center of gravity of the triangle) should be parallel to the x-axis. We can achieve this by rotating the
triangle. Now all that's left is to find the minimum and maximum x coordinate of the vertices of the triangle and
subtract the maximum from the minimum.

*/

#include "geometry.h"
#include "kattisio.h"

#include <cmath>
#include <tuple>
#include <vector>

Point<double> rotate_point(const Point<double> &point, const Point<double> &center, const double &angle_radians)
{
    // translate the point and center so that the center becomes the origin
    double translated_x = point.x - center.x;
    double translated_y = point.y - center.y;

    // perform the rotation
    double rotated_x = translated_x * std::cos(angle_radians) - translated_y * std::sin(angle_radians);
    double rotated_y = translated_x * std::sin(angle_radians) + translated_y * std::cos(angle_radians);

    // translate the point back to its original position
    rotated_x += center.x;
    rotated_y += center.y;

    return Point<double>(rotated_x, rotated_y);
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
    std::vector<Point<double>> vertices{Point<double>(0, 0), Point<double>(a, 0), get_third_vertex(a, b, c)};

    // compute the center of the triangle
    Point<double> center;
    for (const Point<double> &p : vertices)
    {
        center = center + p;
    }
    center = center / 3;

    // given the triangle construction that we used, p2 has the side lengths a and b next to it
    Point<double> vector_from_center_to_rope = (vertices[1] - center).normalized();
    Point<double> vector_positive_yaxis = Point<double>(0, 1);

    // get the angle between the two
    double angle = vector_positive_yaxis.angle(vector_from_center_to_rope);

    // rotate the coordinates by the angle to get the position of how the triangle would hang
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] = rotate_point(vertices[i], center, -angle);
    }

    // get the minimum and maximum x cordinate of the vertices
    double min_x = std::min(vertices[0].x, std::min(vertices[1].x, vertices[2].x));
    double max_x = std::max(vertices[0].x, std::max(vertices[1].x, vertices[2].x));

    return max_x - min_x;
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