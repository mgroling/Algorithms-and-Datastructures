#include "geometry.h"

#include <iostream>

int main()
{
    Point p1 = Point(0, 1);
    Point p2 = Point(4, 9);
    Point p3 = Point(3, -10);
    Point p4 = Point(3, 20);
    std::vector<Point<double>> ps =
        line_segment_intersection(std::pair<Point<int>, Point<int>>{p1, p2}, std::pair<Point<int>, Point<int>>{p3, p4});

    for (const Point<double> &p : ps)
    {
        std::cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}