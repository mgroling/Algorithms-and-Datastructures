// Authors: Marc Gröling

#ifndef geometry_h
#define geometry_h

#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <vector>

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

    Point operator+(const Point &other)
    {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point &other)
    {
        return Point(x - other.x, y - other.y);
    }

    Point operator*(const T &scalar)
    {
        return Point(x * scalar, y * scalar);
    }

    Point operator/(const T &scalar)
    {
        if (scalar == 0)
        {
            throw std::runtime_error("Division by zero encountered!");
        }
        return Point(x / scalar, y / scalar);
    }

    T dot_product(const Point &other)
    {
        return x * other.x + y * other.y;
    }

    // calculates a point/vector that is perpendicular to this one
    Point perpendicular()
    {
        return Point(-y, x);
    }

    T cross_product(const Point &other)
    {
        return x * other.y - y * other.x;
    }

    double magnitude()
    {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    // calculates the euclidean distance between two points
    double distance(const Point &other)
    {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    // returns the angle between two vectors (assumes that the origin of both is the coordinate center) in radians
    double angle(const Point &other)
    {
        return std::atan2(other.y - y, other.x - x);
    }
};

// computes the intersection between two line segments that are the line segments (p, p + r) and (q, q + s)
template <typename T>
std::vector<Point<T>> line_segment_intersection(const Point<T> &p, const Point<T> &r, const Point<T> &q,
                                                const Point<T> &s)
{
    // https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
    T r_cross_s = r.cross_product(s);
    T q_p_cross_r = (q - p).cross_product(r);
    if (r_cross_s == 0 && q_p_cross_r == 0)
    {
    }
}

// takes as input a closed polygon given as a vector of coordinates (x, y)
// reminder: in a closed polygon the last point equals the first one
// this method makes changes on the input vector during computation, but undoes these before returning
template <typename T> double compute_signed_area_polygon(std::vector<Point<T>> &points)
{
    double area = 0;

    if (points.size() % 2 == 0)
    {
        points.push_back(points[0]);
    }

    for (int i = 0; i < points.size() - 1; i += 2)
    {
        area += points[i + 1].x * (points[i + 2].y - points[i].y) + points[i + 1].y * (points[i].x - points[i + 2].x);
    }

    if (points.size() % 2 == 1)
    {
        points.pop_back();
    }

    return area / 2;
}

#endif