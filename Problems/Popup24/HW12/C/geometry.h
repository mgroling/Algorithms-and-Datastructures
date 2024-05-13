// Authors: Marc Gröling

#ifndef geometry_h
#define geometry_h

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <vector>

// epsilon for checking if values are "close" enough to zero
const double EPSILON = 1e-9;

template <typename T> std::pair<T, T> min_max(const T &a, const T &b)
{
    return a < b ? std::pair<T, T>{a, b} : std::pair<T, T>{b, a};
}

template <typename T> class Point
{
  public:
    static_assert(std::is_arithmetic<T>::value, "Point coordinates require a numerical type");

    T x;
    T y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(const T &x, const T &y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const
    {
        return x != other.x || y != other.y;
    }

    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    Point operator*(const T &scalar) const
    {
        return Point(x * scalar, y * scalar);
    }

    Point operator/(const T &scalar) const
    {
        if (scalar == 0)
        {
            throw std::runtime_error("Division by zero encountered!");
        }
        return Point(x / scalar, y / scalar);
    }

    Point<double> copy_double() const
    {
        return Point<double>(x, y);
    }

    T dot_product(const Point &other) const
    {
        return x * other.x + y * other.y;
    }

    // calculates a point/vector that is perpendicular to this one
    Point perpendicular() const
    {
        return Point(-y, x);
    }

    T cross_product(const Point &other) const
    {
        return x * other.y - y * other.x;
    }

    long double magnitude() const
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    Point<double> normalized() const
    {
        double magnitude = this->magnitude();
        return Point<double>(x / magnitude, y / magnitude);
    }

    // calculates the euclidean distance between two points
    double distance(const Point &other) const
    {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    // returns the angle between two vectors (assumes that the origin of both is the coordinate center) in radians
    double angle(const Point &other) const
    {
        return std::atan2(this->cross_product(other), this->dot_product(other));
    }

    // calculates whether the point is within the bounding box generated by s1 and s2 (they mark opposite corners)
    bool is_within(const Point &s1, const Point &s2) const
    {
        std::pair<T, T> min_max_x = min_max(s1.x, s2.x);
        std::pair<T, T> min_max_y = min_max(s1.y, s2.y);
        return min_max_x.first <= x && x <= min_max_x.second && min_max_y.first <= y && y <= min_max_y.second;
    }

    bool on_line_segment(const std::pair<Point, Point> &l) const
    {
        Point u = l.first - *this;
        Point v = l.second - *this;
        return std::abs((u).cross_product(v)) < EPSILON && u.dot_product(v) <= 0;
    }

    double distance_line_segment(const std::pair<Point, Point> &line_segment) const
    {
        if (line_segment.first == line_segment.second)
        {
            return (*this - line_segment.first).magnitude();
        }

        Point direction_segment = line_segment.second - line_segment.first;
        Point vector_to_point1 = (*this - line_segment.first);
        Point vector_to_point2 = (*this - line_segment.second);
        // check if the point lies between the two end points
        if (vector_to_point1.dot_product(direction_segment) >= 0 &&
            vector_to_point2.dot_product(direction_segment) <= 0)
        {
            // distance from point to (infinite) line
            return std::abs((direction_segment).cross_product(vector_to_point1) / direction_segment.magnitude());
        }
        // otherwise the result is the minimum distance to the end points
        return std::min(vector_to_point1.magnitude(), vector_to_point2.magnitude());
    }

    // returns whether or not this point is inside/on/outside of the given polygon
    // 1: point is inside the polygon, 0: point is on a line segment of the polygon, -1: point is outside the polygon
    // assumes that the polygon is closed (first point equals last)
    int inside_polygon(const std::vector<Point<T>> &polygon) const
    {
        assert(polygon[0] == polygon.back() &&
               "Assert failed in Point.inside_polygon: Polygon must be given in closed form.");
        double angle = 0;
        T dot, cross;

        for (int i = 0; i < polygon.size() - 1; i++)
        {
            Point<T> u = polygon[i] - *this;
            Point<T> v = polygon[i + 1] - *this;
            dot = u.dot_product(v);
            cross = u.cross_product(v);
            // point is on this line segment
            if (std::abs(cross) < EPSILON && dot <= 0)
            {
                return 0;
            }
            angle += std::atan2(cross, dot);
        }

        // angle should be 0 if the point is outside an +-2pi if it is inside, select the one that is closer (accounts
        // for rounding errors)
        return std::abs(angle) < M_PI ? -1 : 1;
    }
};

template <typename T> std::ostream &operator<<(std::ostream &os, const Point<T> &p)
{
    os << p.x << ' ' << p.y;
    return os;
}

// calculates whether two line segments intersect
// if they are colinear and overlap, then it returns 2 points (the resulting line segment of all intersection points)
// otherwise if they intersect it returns the intersection point and if they don't, then it simply returns an empty
// vector
template <typename T>
std::vector<Point<long double>> line_segment_intersection(const std::pair<Point<T>, Point<T>> &l1,
                                                          const std::pair<Point<T>, Point<T>> &l2)
{
    long double determinant = (l1.first.x - l1.second.x) * (l2.first.y - l2.second.y) -
                              (l1.first.y - l1.second.y) * (l2.first.x - l2.second.x);
    // case 1: line segments are parallel and may be collinear (are on the same line)
    if (std::abs(determinant) < EPSILON)
    {
        // if they are collinear, then the line segment or point that holds all points of intersections must consist of
        // the end points of the two given line segments
        std::set<std::pair<T, T>> points;
        if (l1.first.on_line_segment(l2))
        {
            points.emplace(l1.first.x, l1.first.y);
        }
        if (l1.second.on_line_segment(l2))
        {
            points.emplace(l1.second.x, l1.second.y);
        }
        if (l2.first.on_line_segment(l1))
        {
            points.emplace(l2.first.x, l2.first.y);
        }
        if (l2.second.on_line_segment(l1))
        {
            points.emplace(l2.second.x, l2.second.y);
        }
        std::vector<Point<long double>> output;
        for (const std::pair<T, T> &point : points)
        {
            output.emplace_back(point.first, point.second);
        }
        return output;
    }
    // case 2: line segments are not parallel and have an intersection point that may lie on both line segments
    // formulas from Wikipedia line segment intersection
    long double t = ((l1.first.x - l2.first.x) * (l2.first.y - l2.second.y) -
                     (l1.first.y - l2.first.y) * (l2.first.x - l2.second.x)) /
                    determinant;
    long double u = -((l1.first.x - l1.second.x) * (l1.first.y - l2.first.y) -
                      (l1.first.y - l1.second.y) * (l1.first.x - l2.first.x)) /
                    determinant;
    if (0 <= t && t <= 1 && 0 <= u && u <= 1)
    {
        return {Point<long double>(l1.first.x + t * (l1.second.x - l1.first.x),
                                   l1.first.y + t * (l1.second.y - l1.first.y))};
    }
    return {};
}

template <typename T>
double line_segment_distance(const std::pair<Point<T>, Point<T>> &l1, const std::pair<Point<T>, Point<T>> &l2)
{
    // lines intersect
    if (line_segment_intersection(l1, l2).size())
    {
        return 0;
    }

    double min = l1.first.distance_line_segment(l2);
    min = std::min(l1.second.distance_line_segment(l2), min);
    min = std::min(l2.first.distance_line_segment(l1), min);
    min = std::min(l2.second.distance_line_segment(l1), min);

    return min;
}

// returns the signed area of a polygon (if the signed area is smaller than 0, then the coordinates are given in
// clockwise fashion, otherwise in counter-clockwise fashion), to get the area, simply take the absolute value
// takes as input a closed polygon given as a vector of coordinates (x, y) reminder: in a closed
// polygon the last point equals the first one
// this method makes changes on the input vector during computation, but undoes these before returning
template <typename T> long double compute_signed_area_polygon(std::vector<Point<T>> &polygon)
{
    assert(polygon[0] == polygon.back() &&
           "Assert failed in compute_signed_area_polygon: Polygon must be given in closed form.");
    long double area = 0;

    if (polygon.size() % 2 == 0)
    {
        polygon.push_back(polygon[0]);
    }

    for (int i = 0; i < polygon.size() - 1; i += 2)
    {
        area +=
            polygon[i + 1].x * (polygon[i + 2].y - polygon[i].y) + polygon[i + 1].y * (polygon[i].x - polygon[i + 2].x);
    }

    if (polygon.size() % 2 == 0)
    {
        polygon.pop_back();
    }

    return area / 2;
}

// computes the closest pair of points in the given vector
// in case of ties, it returns any closest pair
template <typename T> std::pair<Point<T>, Point<T>> closest_pair(std::vector<Point<T>> &points)
{
    Point<T> p1;
    Point<T> p2;
    double distance = std::numeric_limits<double>::max();

    // comparator to sort by x/y value
    auto compare_by_x = [](const Point<T> &a, const Point<T> &b) { return a.x < b.x; };
    auto compare_by_y = [](const Point<T> &a, const Point<T> &b) { return a.y < b.y; };

    // store interesting points ordered by y coordinate
    std::set<Point<T>, decltype(compare_by_y)> interesting_points(compare_by_y);

    // sort points by x coordinate
    std::sort(points.begin(), points.end(), compare_by_x);

    Point<T> other;

    // go through points by increasing x coordinate
    for (const Point<T> &cur : points)
    {
        // get first point with y > cur.y - d
        auto it = interesting_points.upper_bound(Point<T>(0, cur.y - distance));

        // save points to remove for later (removing elements while iterating over an object would lead to undefined
        // behaviour)
        std::vector<Point<T>> to_remove;
        while (it != interesting_points.end())
        {
            other = *it;
            // point is too far away from sweeping line to be of interest anymore
            if (other.x <= cur.x - distance)
            {
                to_remove.push_back(other);
            }

            // point is outside of bounding box that can contain points that are closer than distance
            if (other.y >= cur.y + distance)
            {
                break;
            }

            // update distance
            double temp_dist = (cur - other).magnitude();
            if (temp_dist < distance)
            {
                distance = temp_dist;
                p1 = cur;
                p2 = other;
            }
            it++;
        }

        // remove points that are no longer interesting
        for (const Point<T> &elem : to_remove)
        {
            interesting_points.erase(elem);
        }
        interesting_points.insert(cur);
    }

    return {p1, p2};
}

template <typename T> std::vector<Point<T>> convex_hull(std::vector<Point<T>> &points)
{
    // get the bottom-left point
    Point<T> min_point = points[0];
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].y < min_point.y || (points[i].y == min_point.y && points[i].x < min_point.x))
        {
            min_point = points[i];
        }
    }

    // create function to compare points by angle viewed from min_point (in case of ties, the closer point to min_point
    // should come first)
    auto compare_by_angle = [&](const Point<T> &a, const Point<T> &b) {
        T cross = (a - min_point).cross_product(b - min_point);
        if (std::abs(cross) < EPSILON)
        {
            return (a - min_point).magnitude() < (b - min_point).magnitude();
        }
        return cross > 0;
    };
    std::sort(points.begin(), points.end(), compare_by_angle);

    std::vector<Point<T>> hull{min_point};
    for (const Point<T> p : points)
    {
        if (p == min_point)
        {
            continue;
        }

        // pop points from hull while it is not making a left turn to the new point
        while (hull.size() >= 2 && (hull.back() - hull[hull.size() - 2]).cross_product(p - hull[hull.size() - 2]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    return hull;
}

#endif