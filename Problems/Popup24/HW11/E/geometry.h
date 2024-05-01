// Authors: Marc Gröling

#ifndef geometry_h
#define geometry_h

#include <cassert>
#include <cmath>
#include <iostream>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <vector>

// epislon for checking if values are "close" enough to zero
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

    double magnitude() const
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

    // returns whether or not this point is inside/on/outside of the given polygon
    // 1: point is inside the polygon, 0: point is on a line segment of the polygon, -1: point is outside the polygon
    // assumes that the polygon is closed (first point equals last)
    int inside_polygon(const std::vector<Point<T>> &polygon)
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
std::vector<Point<double>> line_segment_intersection(const std::pair<Point<T>, Point<T>> &l1,
                                                     const std::pair<Point<T>, Point<T>> &l2)
{
    double determinant = (l1.first.x - l1.second.x) * (l2.first.y - l2.second.y) -
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
        std::vector<Point<double>> output;
        for (const std::pair<T, T> &point : points)
        {
            output.emplace_back(point.first, point.second);
        }
        return output;
    }
    // case 2: line segments are not parallel and have an intersection point that may lie on both line segments
    // formulas from Wikipedia line segment intersection
    double t = ((l1.first.x - l2.first.x) * (l2.first.y - l2.second.y) -
                (l1.first.y - l2.first.y) * (l2.first.x - l2.second.x)) /
               determinant;
    double u = -((l1.first.x - l1.second.x) * (l1.first.y - l2.first.y) -
                 (l1.first.y - l1.second.y) * (l1.first.x - l2.first.x)) /
               determinant;
    if (0 <= t && t <= 1 && 0 <= u && u <= 1)
    {
        return {
            Point<double>(l1.first.x + t * (l1.second.x - l1.first.x), l1.first.y + t * (l1.second.y - l1.first.y))};
    }
    return {};
}

// returns the signed area of a polygon (if the signed area is smaller than 0, then the coordinates are given in
// clockwise fashion, otherwise in counter-clockwise fashion), to get the area, simply take the absolute value
// takes as input a closed polygon given as a vector of coordinates (x, y) reminder: in a closed
// polygon the last point equals the first one
// this method makes changes on the input vector during computation, but undoes these before returning
template <typename T> double compute_signed_area_polygon(std::vector<Point<T>> &polygon)
{
    assert(polygon[0] == polygon.back() &&
           "Assert failed in compute_signed_area_polygon: Polygon must be given in closed form.");
    double area = 0;

    if (polygon.size() % 2 == 0)
    {
        polygon.push_back(polygon[0]);
    }

    for (int i = 0; i < polygon.size() - 1; i += 2)
    {
        area +=
            polygon[i + 1].x * (polygon[i + 2].y - polygon[i].y) + polygon[i + 1].y * (polygon[i].x - polygon[i + 2].x);
    }

    if (polygon.size() % 2 == 1)
    {
        polygon.pop_back();
    }

    return area / 2;
}

#endif