#include "ford_fulkerson.h"
#include "graph.h"
#include "kattisio.h"

int matrix_pos_to_int(const int &row, const int &col, const int &num_cols)
{
    return row * num_cols + col;
}

bool solve_problem(const std::pair<std::vector<int>, std::vector<int>> problem)
{
    int num_rows = problem.first.size();
    int num_cols = problem.second.size();
    int source = 0;
    int target = num_rows * num_cols + num_rows + num_cols + 1;
    int offset_variables = 1;
    int offset_equations_row_sums = offset_variables + num_rows * num_cols;
    int offset_equations_col_sums = offset_equations_row_sums + num_rows;

    AdjacencyListGraph g = AdjacencyListGraph(num_rows * num_cols + num_rows + num_cols + 2);
    int variable_id;
    int all_equation_sum = 0;

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            variable_id = offset_variables + matrix_pos_to_int(i, j, num_cols);
            // create edges from source to layer 1 (variables)
            g.addEdge(source, variable_id, 1, false);
            g.addEdge(variable_id, source, 0, false);

            // create edges from layer 1 (variables) to layer 2 (equations)
            // to its row sum
            g.addEdge(variable_id, offset_equations_row_sums + i, 1, false);
            g.addEdge(offset_equations_row_sums + i, variable_id, 0, false);

            // to its col sum
            g.addEdge(variable_id, offset_equations_col_sums + j, 1, false);
            g.addEdge(offset_equations_col_sums + j, variable_id, 0, false);
        }

        // from row equations to target
        g.addEdge(offset_equations_row_sums + i, target, problem.first[i], false);
        all_equation_sum += problem.first[i];
        g.addEdge(target, offset_equations_row_sums + i, 0, false);
    }

    for (int i = 0; i < num_cols; i++)
    {
        // from col equations to target
        g.addEdge(offset_equations_col_sums + i, target, num_rows - problem.second[i], false);
        all_equation_sum += num_rows - problem.second[i];
        g.addEdge(target, offset_equations_col_sums + i, 0, false);
    }

    return all_equation_sum == (int)ford_fulkerson(g, source, target);
}