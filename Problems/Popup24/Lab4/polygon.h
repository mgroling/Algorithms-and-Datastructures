// Authors: Marc Gröling

#include <vector>

// takes as input a closed polygon given as a vector of coordinates (x, y)
// reminder: in a closed polygon the last point equals the first one
// this method makes changes on the input vector during computation, but undoes these before returning
double compute_signed_area_polygon(std::vector<std::pair<int, int>> &points)
{
    double area = 0;

    if (points.size() % 2 == 0)
    {
        points.push_back(points[0]);
    }

    for (int i = 0; i < points.size() - 1; i += 2)
    {
        area += points[i + 1].first * (points[i + 2].second - points[i].second) +
                points[i + 1].second * (points[i].first - points[i + 2].first);
    }

    if (points.size() % 2 == 1)
    {
        points.pop_back();
    }

    return area / 2;
}