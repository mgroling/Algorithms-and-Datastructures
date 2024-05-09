/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "geometry.h"

#include <algorithm>
#include <limits>
#include <vector>

std::pair<int, std::vector<long double>> solve_problem(std::pair<std::vector<Point<long double>>, long double> &problem)
{
    std::vector<Point<long double>> vertices = std::move(problem.first);
    long double min_area_section = problem.second;

    // calculate area of the whole boat and how much each section will occupy
    vertices.push_back(vertices[0]);
    long double area_boat = std::abs(compute_signed_area_polygon(vertices));
    int num_sections = area_boat / min_area_section;
    long double area_section = area_boat / num_sections;
    vertices.pop_back();

    // separate vertices into two parts (representing the two horizontal "lines")
    long double min_x = std::numeric_limits<long double>::max();
    int min_index = -1;
    long double max_x = std::numeric_limits<long double>::min();
    int max_index = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].x < min_x)
        {
            min_x = vertices[i].x;
            min_index = i;
        }
        if (vertices[i].x > max_x)
        {
            max_x = vertices[i].x;
            max_index = i;
        }
    }

    // going from max to min in counter-clockwise order (top part)
    std::vector<Point<long double>> vertices_part1;
    for (int i = max_index; i != min_index; i = (i + 1) % vertices.size())
    {
        vertices_part1.push_back(vertices[i]);
    }
    // going from max to min in clockwise order (bottom part)
    std::vector<Point<long double>> vertices_part2;
    for (int i = max_index; i != min_index; i = (i + vertices.size() - 1) % vertices.size())
    {
        vertices_part2.push_back(vertices[i]);
    }

    return {num_sections, {}};
}