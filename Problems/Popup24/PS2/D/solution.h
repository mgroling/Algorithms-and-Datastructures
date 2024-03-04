
#include "kattisio.h"

#include <cmath>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

int manhattan_distance(int x_0, int y_0, int x_1, int y_1)
{
    return std::abs(x_0 - x_1) + std::abs(y_0 - y_1);
}

void bfs_distances_base(std::vector<std::vector<int>> &distances, int base_x, int base_y, int num_x, int num_y)
{
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(base_x, base_y, 0);
    distances[base_x][base_y] = 0;

    while (!q.empty())
    {
        int x, y, dist;
        std::tie(x, y, dist) = q.front();
        q.pop();

        // right
        if (x + 1 < num_x && dist + 1 < distances[x + 1][y])
        {
            distances[x + 1][y] = dist + 1;
            q.emplace(x + 1, y, dist + 1);
        }
        // left
        if (x - 1 >= 0 && dist + 1 < distances[x - 1][y])
        {
            distances[x - 1][y] = dist + 1;
            q.emplace(x - 1, y, dist + 1);
        }
        // down
        if (y + 1 < num_y && dist + 1 < distances[x][y + 1])
        {
            distances[x][y + 1] = dist + 1;
            q.emplace(x, y + 1, dist + 1);
        }
        // up
        if (y - 1 >= 0 && dist + 1 < distances[x][y - 1])
        {
            distances[x][y - 1] = dist + 1;
            q.emplace(x, y - 1, dist + 1);
        }
    }
}

int bfs(const std::vector<std::vector<int>> &distances, std::pair<int, int> start, std::pair<int, int> end,
        int allowed_distance, int num_x, int num_y)
{
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(start.first, start.second, 0);
    std::vector<std::vector<bool>> visited(num_x, std::vector<bool>(num_y, false));
    visited[start.first][start.second] = true;

    while (!q.empty())
    {
        int x, y, dist;
        std::tie(x, y, dist) = q.front();
        q.pop();

        if (x == end.first && y == end.second)
        {
            return dist;
        }

        // right
        if (x + 1 < num_x && distances[x + 1][y] >= allowed_distance && !visited[x + 1][y])
        {
            q.emplace(x + 1, y, dist + 1);
            visited[x + 1][y] = true;
        }
        // left
        if (x - 1 >= 0 && distances[x - 1][y] >= allowed_distance && !visited[x - 1][y])
        {
            q.emplace(x - 1, y, dist + 1);
            visited[x - 1][y] = true;
        }
        // down
        if (y + 1 < num_y && distances[x][y + 1] >= allowed_distance && !visited[x][y + 1])
        {
            q.emplace(x, y + 1, dist + 1);
            visited[x][y + 1] = true;
        }
        // up
        if (y - 1 >= 0 && distances[x][y - 1] >= allowed_distance && !visited[x][y - 1])
        {
            q.emplace(x, y - 1, dist + 1);
            visited[x][y - 1] = true;
        }
    }

    return -1;
}

std::pair<int, int> solve_problem(Test_case test_case)
{
    std::vector<std::vector<int>> distance_to_closest_base(
        test_case.num_x_grid, std::vector<int>(test_case.num_y_grid, std::numeric_limits<int>::max()));

    for (const std::pair<int, int> &base : test_case.bases)
    {
        bfs_distances_base(distance_to_closest_base, base.first, base.second, test_case.num_x_grid,
                           test_case.num_y_grid);
    }

    int min = 0;
    int max = distance_to_closest_base[test_case.start_pos.first][test_case.start_pos.second];
    int middle;
    int dist;

    while (min <= max)
    {
        middle = (min + max) / 2;
        dist = bfs(distance_to_closest_base, test_case.start_pos, test_case.end_pos, middle, test_case.num_x_grid,
                   test_case.num_y_grid);
        int dist_middle_plus1 = bfs(distance_to_closest_base, test_case.start_pos, test_case.end_pos, middle + 1,
                                    test_case.num_x_grid, test_case.num_y_grid);

        if (dist != -1 && dist_middle_plus1 == -1)
        {
            return std::pair{middle, dist};
        }
        if (dist == -1)
        {
            max = middle - 1;
        }
        else
        {
            min = middle + 1;
        }
    }

    return std::pair{middle, dist};
}