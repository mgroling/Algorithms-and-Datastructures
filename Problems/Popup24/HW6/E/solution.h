/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Binary tomography deals with the problem of reconstructing binary images from a small number of projections. One of its
most basic problems is to construct a binary ({0, 1}-valued) matrix with given row and column sums. This is not always
possible and your task is to determine when it is.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains two numbers 1 <= m, n <= 1000 the number of rows and columns of the matrix. The next
line contains m numbers 0 <= r_i <= n – the sum of each row in the matrix. The third line contains numbers 0 <= c_j <= m
– the sum of each column in the matrix.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Output “Yes” if there exists an m-by-n matrix, with each element either being 0 or 1, such that the sum of row i equals
r_i for all rows and the sum of column j equals r_j for all columns. Otherwise output “No”.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

A possible solution for sample input 1 looks like this:
_________
|X| |X| | 2
| |X|X|X| 3
| | |X|X| 2

 1 1 3 2

Sample Input 1:
3 4
2 3 2
1 1 3 2

Sample Output 1:
Yes

Sample Input 2:
3 3
0 0 3
0 0 3

Sample Output 2:
No

----------------------------------------------------- SOLUTION -----------------------------------------------------

The problem can be solved recursively. We can remove any row from the matrix with row sum r_i, then we have to decrement
r_i column sums and we do that from largest to smallest. We keep doing that until either, (1) we cannot decrement enough
columns for a row (in which case it's not posible), or (2) there are no rows left. In (2), now we only have to check if
all column sums are zero and if yes, then it is possible.

*/

#include "kattisio.h"

#include <algorithm>
#include <vector>

bool solve_problem_recursive(std::vector<int> &row_sums, std::vector<int> &col_sums)
{
    // if there are no more rows left, we are done
    if (!row_sums.size())
    {
        // check that the largest (so all) columns are zero
        return col_sums[0] == 0;
    }

    // remove the last row
    int last_row_sum = row_sums.back();
    row_sums.pop_back();

    // remove 1 from the last_row_sum'th largest columns
    for (int i = 0; i < last_row_sum; i++)
    {
        if (col_sums[i])
        {
            col_sums[i]--;
        }
        else
        {
            return false;
        }
    }

    // need to sort col_sums again (could also do it in a faster way (since we only decrement the first k elements by
    // 1), but this is fast enough anyway)
    std::sort(col_sums.begin(), col_sums.end(), std::greater<int>());

    return solve_problem_recursive(row_sums, col_sums);
}

bool solve_problem(std::vector<int> &row_sums, std::vector<int> &col_sums)
{
    // sort columns descendingly
    std::sort(col_sums.begin(), col_sums.end(), std::greater<int>());

    return solve_problem_recursive(row_sums, col_sums);
}