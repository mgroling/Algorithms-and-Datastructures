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

// Spot goes from last_toy to toy and is anchored at anchor_points[-1]
// TODO: need to do unwrapping logic in here as well, since they are not independent (maybe in popping from hull phase
// just include all anchors? and depending on ccw + right/// logic pop)
void insert_wrapped_trees(const Point<int> &toy, const Point<int> &last_toy,
                          std::vector<std::pair<Point<int>, bool>> &anchor_points, const std::vector<Point<int>> &trees,
                          double &max_distance, const double &distance_to_anchor)
{
    Point<int> anchor = anchor_points.back().first;
    // create a triangle that marks the area where the leash passes (closed polygon)
    std::vector<Point<int>> triangle = {anchor, last_toy, toy, anchor};

    // only consider trees that are in this triangle
    std::vector<Point<int>> interesting_trees;
    for (const Point<int> &tree : trees)
    {
        if (tree.inside_polygon(triangle) == 1)
        {
            interesting_trees.push_back(tree);
        }
    }

    // check if we do a right or left turn from anchor_points[-1] to last_toy to toy
    int cross = (last_toy - anchor).cross_product(toy - last_toy);
    // Spot moves straight => can't get the leash stuck on any trees
    if (cross == 0)
    {
        // simply check if the distance increases
        max_distance =
            std::max(max_distance, distance_to_anchor + (last_toy - anchor).magnitude() + (toy - last_toy).magnitude());
    }
    // Spot does a left turn
    else if (cross > 0)
    {
        // sort the interesting trees based on their angle (trees further on the right should come first)
        auto compare_by_angle = [anchor](const Point<int> &a, const Point<int> &b) {
            int cross = (a - anchor).cross_product(b - anchor);
            if (cross == 0)
            {
                return (a - anchor).magnitude() < (b - anchor).magnitude();
            }
            return cross > 0;
        };
        std::sort(interesting_trees.begin(), interesting_trees.end(), compare_by_angle);
        // also add toy to interesting trees, since it should be the last point of the mini-convex hull
        interesting_trees.push_back(toy);

        std::vector<Point<int>> trees_to_add{anchor};
        for (const Point<int> &tree : interesting_trees)
        {
            // pop points from trees_to_add while it is making right turns
            while (trees_to_add.size() >= 2 && (trees_to_add.back() - trees_to_add[trees_to_add.size() - 2])
                                                       .cross_product(tree - trees_to_add[trees_to_add.size() - 2]) < 0)
            {
                trees_to_add.pop_back();
            }
            trees_to_add.push_back(tree);
        }

        double temp_distance = distance_to_anchor + (anchor - trees_to_add[0]).magnitude();
        // calculate distance that the leash takes wrapped around these new anchor points and from the last to toy
        for (int i = 0; i < trees_to_add.size() - 1; i++)
        {
            temp_distance += (trees_to_add[i] - trees_to_add[i + 1]).magnitude();
        }
        max_distance = std::max(max_distance, temp_distance);

        // remove toy from interesting trees again, since it is no anchor point
        trees_to_add.pop_back();

        // add the new anchor points
        for (const Point<int> &tree : trees_to_add)
        {
            if (tree != anchor)
            {
                // since Spot did a left turn, the leash is wrapped counter-clockwise around all those trees
                anchor_points.emplace_back(tree, false);
            }
        }
    }
    // Spot does a right turn
    else
    {
        // sort the interesting trees based on their angle (trees further on the left should come first)
        auto compare_by_angle = [anchor](const Point<int> &a, const Point<int> &b) {
            int cross = (a - anchor).cross_product(b - anchor);
            if (cross == 0)
            {
                return (a - anchor).magnitude() < (b - anchor).magnitude();
            }
            return cross < 0;
        };
        std::sort(interesting_trees.begin(), interesting_trees.end(), compare_by_angle);
        // also add toy to interesting trees, since it should be the last point of the mini-convex hull
        interesting_trees.push_back(toy);

        std::vector<Point<int>> trees_to_add{anchor};
        for (const Point<int> &tree : interesting_trees)
        {
            // pop points from trees_to_add while it is making left turns
            while (trees_to_add.size() >= 2 && (trees_to_add.back() - trees_to_add[trees_to_add.size() - 2])
                                                       .cross_product(tree - trees_to_add[trees_to_add.size() - 2]) > 0)
            {
                trees_to_add.pop_back();
            }
            trees_to_add.push_back(tree);
        }

        double temp_distance = distance_to_anchor + (anchor - trees_to_add[0]).magnitude();
        // calculate distance that the leash takes wrapped around these new anchor points and from the last to toy
        for (int i = 0; i < trees_to_add.size() - 1; i++)
        {
            temp_distance += (trees_to_add[i] - trees_to_add[i + 1]).magnitude();
        }
        max_distance = std::max(max_distance, temp_distance);

        // remove toy from interesting trees again, since it is no anchor point
        trees_to_add.pop_back();

        // add the new anchor points
        for (const Point<int> &tree : trees_to_add)
        {
            if (tree != anchor)
            {
                // since Spot did a right turn, the leash is wrapped clockwise around all those trees
                anchor_points.emplace_back(tree, true);
            }
        }
    }
}

double solve_problem(const std::pair<std::vector<Point<int>>, std::vector<Point<int>>> &problem)
{
    double max_distance = 0;

    std::vector<Point<int>> toys = std::move(problem.first);
    std::vector<Point<int>> trees = std::move(problem.second);
}