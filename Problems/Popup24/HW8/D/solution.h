/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "prime_sieve.h"

#include <cmath>
#include <vector>

std::vector<long long> solve_problem(const std::vector<long long> &input)
{
    std::vector<long long> output;

    for (const long long &elem : input)
    {
        std::vector<long long> non_trivial_factors = find_non_trivial_factors(elem);
        // all numbers except 1 have at least 3 lines (using n (1x1) blocks, and (nx1) + (1xn))
        long long sum = elem == 1 ? 1 : 3;

        for (const long long &block_size : non_trivial_factors)
        {
            // blocks of 1 * block_size (horizontally + vertically)
            sum += 2;
            for (const long long &num_blocks : non_trivial_factors)
            {
                if (elem % (block_size * num_blocks) == 0)
                {
                    // blocks of num_blocks * block_size (horizontally + vertically)
                    sum += 2;
                }
            }
        }

        output.push_back(sum);
    }

    return output;
}

struct Point
{
    double x;
    double y;
};

bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) &&
        q.y >= std::min(p.y, r.y))
        return true;
    return false;
}

int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;             // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false;
}

bool isIntersectSquare(Point squareBottomLeft, Point squareTopRight, double a, double b)
{
    Point lineStart = {0, 0};
    Point lineEnd = {a, b};

    // Define the four corners of the square
    Point topLeft = {squareTopRight.x, squareBottomLeft.y};
    Point bottomRight = {squareBottomLeft.x, squareTopRight.y};

    // Check if any of the line segments formed by the square intersect with the given line segment
    if (doIntersect(squareBottomLeft, topLeft, lineStart, lineEnd))
        return true;
    if (doIntersect(topLeft, squareTopRight, lineStart, lineEnd))
        return true;
    if (doIntersect(squareTopRight, bottomRight, lineStart, lineEnd))
        return true;
    if (doIntersect(bottomRight, squareBottomLeft, lineStart, lineEnd))
        return true;

    return false;
}

bool line_is_correct(const int &a, const int &b, const int &n)
{
    int sum = 0;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            sum += isIntersectSquare(Point{(double)i, (double)j}, Point{(double)i + 1, (double)j + 1}, a, b);
        }
    }

    return sum == n;
}

long long solve_test_case(const long long &n)
{
    long long sum = 0;
    for (int a = 1; a <= n; a++)
    {
        for (int b = 1; b <= n; b++)
        {
            sum += line_is_correct(a, b, n);
        }
    }
    return sum;
}

std::vector<long long> solve_problem_naive(const std::vector<long long> &input)
{
    std::vector<long long> output;

    for (const long long &elem : input)
    {
        output.push_back(solve_test_case(elem));
    }

    return output;
}