#include "geometry.h"

#include <iostream>

int main()
{
    Point p1 = Point(1, 1);
    Point p2 = Point(2, 2);
    Point p3 = Point(2, 2);
    Point p4 = Point(4, 4);

    std::cout << p1.distance_line_segment({p2, p3}) << '\n';

    return 0;
}