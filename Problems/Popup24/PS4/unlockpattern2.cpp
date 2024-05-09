#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @file Point.hpp
 * @brief Contains the class Point that represents a point in a 2D plane.
 * @usage Construct a point with the default constructor or the parameterized
 * constructor. Perform point-point and point-scalar operations. Calculate the
 * dot and cross products. Calculate the distance between two points. Check if
 * a point is on a line segment. Calculate the angle between three points.
 * @tparam T The type of the coordinates of the point.
 * @author Isak Reinholdsson
 */

#ifndef POINT_HPP
#define POINT_HPP

#include <cmath>     // For std::sqrt, std::atan2
#include <iostream>  // For std::ostream, std::istream
#include <limits>    // For std::numeric_limits
#include <stdexcept> // For std::runtime_error

/**
 * @brief Represents a point in a 2D plane.
 * @usage Construct a point with the default constructor or the parameterized
 * constructor. Perform point-point and point-scalar operations. Calculate the
 * dot and cross products. Calculate the distance between two points. Check if
 * a point is on a line segment. Calculate the angle between three points.
 * @tparam T The type of the coordinates of the point.
 */
template <typename T> class Point
{
  public:
    // Coordinates
    T x, y;

    // Default constructor initializes to zero
    Point() : x(0), y(0)
    {
    }

    // Parameterized constructor
    Point(T x, T y) : x(x), y(y)
    {
    }

    // Addition with another point results in a Point whose type is the result
    // of T + U
    template <typename U> Point<decltype(T() + U())> operator+(const Point<U> &p) const
    {
        return Point<decltype(T() + U())>(x + p.x, y + p.y);
    }

    // Addition with a scalar results in a Point whose type is the result of
    // T + U
    template <typename U> Point<decltype(T() + U())> operator+(U scalar) const
    {
        return Point<decltype(T() + U())>(x + scalar, y + scalar);
    }

    // Subtraction with another point results in a Point whose type is the
    // result of T - U
    template <typename U> Point<decltype(T() - U())> operator-(const Point<U> &p) const
    {
        return Point<decltype(T() - U())>(x - p.x, y - p.y);
    }

    // Subtraction with a scalar results in a Point whose type is the result of
    // T - U
    template <typename U> Point<decltype(T() - U())> operator-(U scalar) const
    {
        return Point<decltype(T() - U())>(x - scalar, y - scalar);
    }

    // Multiplied by scalar results in a Point whose type is the result of T * U
    template <typename U> Point<decltype(T() * U())> operator*(U scalar) const
    {
        return Point<decltype(T() * U())>(x * scalar, y * scalar);
    }

    // Division by scalar results in a Point whose type is the result of T / U
    template <typename U> Point<decltype(T() / U())> operator/(U scalar) const
    {
        if (scalar == 0)
        {
            throw std::runtime_error("Division by zero.");
        }
        return Point<decltype(T() / U())>(x / scalar, y / scalar);
    }

    // Angle between point and two other points
    template <typename U, typename V> double angle(const Point<U> &p1, const Point<V> &p2) const
    {
        Point<U> v1 = p1 - *this;
        Point<V> v2 = p2 - *this;
        double dotProduct = v1 * v2;
        double crossProduct = v1 ^ v2;
        return std::atan2(crossProduct, dotProduct);
    }

    // Distance between two points (double)
    double dist(const Point<T> &p) const
    {
        T dx = x - p.x;
        T dy = y - p.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Norm of the point (double)
    double norm() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Check if the point is on the line segment defined by p1 and p2
    bool isOnLineSegment(const Point<T> &p1, const Point<T> &p2) const
    {
        T crossProduct = (p2.x - p1.x) * (y - p1.y) - (p2.y - p1.y) * (x - p1.x);
        if (std::abs(crossProduct) > std::numeric_limits<T>::epsilon())
        {
            return false; // Not collinear
        }
        return std::min(p1.x, p2.x) <= x && x <= std::max(p1.x, p2.x) && std::min(p1.y, p2.y) <= y &&
               y <= std::max(p1.y, p2.y);
    }

    // Dot prouct between two points of type T and U results in a type of T * U
    template <typename U> decltype(T() * U()) dot(const Point<U> &p) const
    {
        return x * p.x + y * p.y;
    }

    // Overload the * operator to calculate the dot product
    template <typename U> decltype(T() * U()) operator*(const Point<U> &p) const
    {
        return dot(p);
    }

    // Cross product between two points of type T and U results in a type of T *
    // U
    template <typename U> decltype(T() * U()) cross(const Point<U> &p) const
    {
        return x * p.y - y * p.x;
    }

    // Overload the ^ operator to calculate the cross product
    template <typename U> decltype(T() * U()) operator^(const Point<U> &p) const
    {
        return cross(p);
    }

    // Equality operator
    bool operator==(const Point<T> &p) const
    {
        return (x == p.x && y == p.y);
    }

    // Inequality operator
    bool operator!=(const Point<T> &p) const
    {
        return !(*this == p);
    }

    // Less than operator (note that this sorts first by x and then by y)
    bool operator<(const Point<T> &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }

    // Stream insertion
    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << p.x << " " << p.y;
        return os;
    }

    // Stream extraction
    friend std::istream &operator>>(std::istream &is, Point &p)
    {
        is >> p.x >> p.y;
        return is;
    }
};
#endif // POINT_HPP

#include <cmath>

#define endl '\n'
using namespace std;

#define OUR_PI 3.1415926532

vector<Point<int>> intToPoint;

bool isValid(vector<int> &nums)
{
    vector<bool> visited(10, false);

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int j = i + 1;
        int a = min(nums[i], nums[j]);
        int b = max(nums[i], nums[j]);

        if (a == 1 && b == 7 && !visited[4])
            return false;
        if (a == 2 && b == 8 && !visited[5])
            return false;
        if (a == 3 && b == 9 && !visited[6])
            return false;
        if (a == 1 && b == 3 && !visited[2])
            return false;
        if (a == 4 && b == 6 && !visited[5])
            return false;
        if (a == 7 && b == 9 && !visited[8])
            return false;
        if (a == 1 && b == 9 && !visited[5])
            return false;
        if (a == 3 && b == 7 && !visited[5])
            return false;

        visited[a] = true;
        visited[b] = true;
    }

    return true;
}

bool isValue(double a, double b)
{
    return abs(a - b) < 0.00001;
}

string sequence(vector<int> &nums)
{
    string s;

    for (int i = 0; i < nums.size() - 2; i++)
    {
        int j = i + 1;
        int k = j + 1;

        int a = nums[i];
        int b = nums[j];
        int c = nums[k];

        double angle = intToPoint[b].angle(intToPoint[a], intToPoint[c]);

        if (isValue(angle, OUR_PI) || isValue(angle, -OUR_PI))
        {
            s += 'S';
        }
        else if (isValue(angle, 0))
        {
            s += 'A';
        }
        else if (angle < 0)
        {
            s += 'L';
        }
        else
        {
            s += 'R';
        }
    }
    return s;
}

bool equalString(string &s1, string &s2)
{
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] == '?')
        {
            continue;
        }

        if (s1[i] != s2[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed << setprecision(20);

    string s = "LRRRSRL";
    // cin >> s;
    intToPoint = {Point<int>(0, 0), Point<int>(0, 2), Point<int>(1, 2), Point<int>(2, 2), Point<int>(0, 1),
                  Point<int>(1, 1), Point<int>(2, 1), Point<int>(0, 0), Point<int>(1, 0), Point<int>(2, 0)};

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // vector<int> nums = {2, 5, 3, 6, 7, 4, 1, 8, 9};

    int counter = 0;

    while (true)
    {
        if (isValid(nums))
        {
            string s2 = sequence(nums);
            // cout << s << endl;
            // cout << s2 << endl;

            if (equalString(s, s2))
            {
                counter++;
            }
        }

        if (!next_permutation(nums.begin(), nums.end()))
            break;
    }

    cout << counter << endl;

    return 0;
}
