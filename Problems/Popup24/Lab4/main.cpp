#include "geometry.h"

#include <iostream>

int main()
{
    Point<double> p1 = Point<double>(3, 1);
    Point<double> p2 = Point<double>(5, 2);
    Point<double> p3 = Point<double>(1, 2);
    Point<double> p4 = Point<double>(4, 4);

    std::vector<Point<double>> points{p1, p2, p3, p4};
    closest_pair(points);

    return 0;
}