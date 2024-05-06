/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include "geometry.h"

#include <algorithm>
#include <vector>

// Spot goes from start to toy and is anchored at anchor_points[-1]
void insert_wrapped_trees(const Point<long double> &toy, const Point<long double> &start,
                          std::vector<std::pair<Point<long double>, int>> &anchor_points,
                          const std::vector<Point<long double>> &trees, long double &max_distance,
                          const long double &distance_to_anchor)
{
    Point<long double> anchor = anchor_points.back().first;
    // create a triangle that marks the area where the leash passes (closed polygon)
    std::vector<Point<long double>> triangle = {anchor, start, toy, anchor};

    // only consider trees that are in this triangle
    std::vector<Point<long double>> interesting_trees;
    for (const Point<long double> &tree : trees)
    {
        if (tree.inside_polygon(triangle) == 1)
        {
            interesting_trees.push_back(tree);
        }
    }

    // check if we do a right or left turn from anchor_points[-1] to start to toy
    long double cross = (start - anchor).cross_product(toy - start);
    // Spot moves straight => can't get the leash stuck on any trees
    if (std::abs(cross) < EPSILON)
    {
        // simply check if the distance increases
        max_distance =
            std::max(max_distance, distance_to_anchor + (start - anchor).magnitude() + (toy - start).magnitude());
    }
    // Spot does a left turn
    else if (cross > 0)
    {
        // sort the interesting trees based on their angle (trees further on the right should come first)
        auto compare_by_angle = [anchor](const Point<long double> &a, const Point<long double> &b) {
            long double cross = (a - anchor).cross_product(b - anchor);
            if (std::abs(cross) < EPSILON)
            {
                return (a - anchor).magnitude() < (b - anchor).magnitude();
            }
            return cross > 0;
        };
        std::sort(interesting_trees.begin(), interesting_trees.end(), compare_by_angle);
        // also add toy to interesting trees, since it should be the last point of the mini-convex hull
        interesting_trees.push_back(toy);

        std::vector<Point<long double>> trees_to_add{anchor};
        for (const Point<long double> &tree : interesting_trees)
        {
            // pop points from trees_to_add while it is making right turns
            while (trees_to_add.size() >= 2 && (trees_to_add.back() - trees_to_add[trees_to_add.size() - 2])
                                                       .cross_product(tree - trees_to_add[trees_to_add.size() - 2]) < 0)
            {
                trees_to_add.pop_back();
            }
            trees_to_add.push_back(tree);
        }

        long double temp_distance = distance_to_anchor + (anchor - trees_to_add[0]).magnitude();
        // calculate distance that the leash takes wrapped around these new anchor points and from the last to toy
        for (int i = 0; i < trees_to_add.size() - 1; i++)
        {
            temp_distance += (trees_to_add[i] - trees_to_add[i + 1]).magnitude();
        }
        max_distance = std::max(max_distance, temp_distance);

        // remove toy from interesting trees again, since it is no anchor point
        trees_to_add.pop_back();

        // add the new anchor points
        for (const Point<long double> &tree : trees_to_add)
        {
            if (tree != anchor)
            {
                // since Spot did a left turn, the leash is wrapped counter-clockwise around all those trees
                anchor_points.emplace_back(tree, -1);
            }
        }
    }
    // Spot does a right turn
    else
    {
        // sort the interesting trees based on their angle (trees further on the left should come first)
        auto compare_by_angle = [anchor](const Point<long double> &a, const Point<long double> &b) {
            long double cross = (a - anchor).cross_product(b - anchor);
            if (std::abs(cross) < EPSILON)
            {
                return (a - anchor).magnitude() < (b - anchor).magnitude();
            }
            return cross < 0;
        };
        std::sort(interesting_trees.begin(), interesting_trees.end(), compare_by_angle);
        // also add toy to interesting trees, since it should be the last point of the mini-convex hull
        interesting_trees.push_back(toy);

        std::vector<Point<long double>> trees_to_add{anchor};
        for (const Point<long double> &tree : interesting_trees)
        {
            // pop points from trees_to_add while it is making left turns
            while (trees_to_add.size() >= 2 && (trees_to_add.back() - trees_to_add[trees_to_add.size() - 2])
                                                       .cross_product(tree - trees_to_add[trees_to_add.size() - 2]) > 0)
            {
                trees_to_add.pop_back();
            }
            trees_to_add.push_back(tree);
        }

        long double temp_distance = distance_to_anchor + (anchor - trees_to_add[0]).magnitude();
        // calculate distance that the leash takes wrapped around these new anchor points and from the last to toy
        for (int i = 0; i < trees_to_add.size() - 1; i++)
        {
            temp_distance += (trees_to_add[i] - trees_to_add[i + 1]).magnitude();
        }
        max_distance = std::max(max_distance, temp_distance);

        // remove toy from interesting trees again, since it is no anchor point
        trees_to_add.pop_back();

        // add the new anchor points
        for (const Point<long double> &tree : trees_to_add)
        {
            if (tree != anchor)
            {
                // since Spot did a right turn, the leash is wrapped clockwise around all those trees
                anchor_points.emplace_back(tree, +1);
            }
        }
    }
}

void unwrap_leash(const Point<long double> &toy, const Point<long double> &start,
                  std::vector<std::pair<Point<long double>, bool>> &anchor_points,
                  const std::vector<Point<long double>> &trees)
{
    // leash is only wrapped around initial point, from which it cannot unwrap
    if (anchor_points.size() == 1)
    {
        return;
    }

    Point<long double> anchor = anchor_points.back().first;
    Point<long double> prev_anchor = anchor_points[anchor_points.size() - 2].first;
    // wrap > 0 clockwise, wrap < 0 counter-clockwise
    int wrap = anchor_points.back().second;

    // check if we do a right or left turn from anchor_points[-2] to anchor_points[-1] to toy
    long double cross = (start - anchor).cross_product(toy - start);
    // Spot moves straight => can't get the leash unstuck on trees
    if (std::abs(cross) < EPSILON)
    {
        return;
    }
    // Spot does a left turn
    else if (cross > 0)
    {
        if (wrap)
        {
        }
    }
    // Spot does a right turn
    else
    {
    }
}

double solve_problem(const std::pair<std::vector<Point<long double>>, std::vector<Point<long double>>> &problem)
{
    double max_distance = 0;

    std::vector<Point<long double>> toys = std::move(problem.first);
    std::vector<Point<long double>> trees = std::move(problem.second);
}