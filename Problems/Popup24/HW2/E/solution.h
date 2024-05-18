/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

Frane has been given the task of sorting an array of numbers. The array consists of N integers, each between 1 and N
(inclusive), with each of those appearing exactly once in the array. Frane has come up with the following sorting
algorithm which operates in N phases, and named it turbosort:

    -In the first phase, the number 1 is moved to position 1 by repeatedly swapping consecutive elements.

    -In the second phase, the number N is moved to position N in the same manner.

    -In the third phase, the number 2 is moved to position 2.

    -In the fourth phase, the number N-1 is moved to position N-1.

    -And so on...

In other words, when the number of the phase is odd, Frane will choose the smallest number not yet chosen, and move it
to its final position. In even phases he chooses the largest number not yet chosen. Write a program which, given the
initial array, output the number of swaps in each phase of the algorithm.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line contains an integer N (1 <= N <= 100 000), the number of elements in the array. Each of the following N
lines contains an integer between 1 and N (inclusive), the array to be sorted. The array will contain no duplicates.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each of the N phases, output the number of swaps on a single line.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input 1:
3
2
1
3

Sample Output 1:
1
0
0

Sample Input 2:
5
5
4
3
2
1

Sample Output 2:
4
3
2
1
0

Sample Input 3:
7
5
4
3
7
1
2
6

Sample Output 3:
4
2
3
0
2
1
0

----------------------------------------------------- SOLUTION -----------------------------------------------------

Notice that if we put an element Y at its correct position, then we need to do X swaps, where X is the number of
elements that are to the left of Y in the initial array and are greater than Y.

That is:
5 4 3 2 1 -> 1 5 4 3 2 (basically, we just shift all untouched elements to the left of 1 by 1 place to the right and
then put 1 in the first position)

Now we need to count how many untouched elements are before a number. We can use a 1-or-0 array that represents whether
an element has been touched yet. Updating this array naively would take O(n^2) time which would be too slow. Instead we
can use Fenwick-Trees to do this efficiently.

*/

#include <vector>

// get the value of the least-significant bit in x
int lsb(int x)
{
    return x & (-x);
}

// data structure to support getting sums of arbitrary ranges of a dynamic array A = A[0], .. A[n - 1]
// this data structure is 0-indexed
class Fenwick_Tree
{
  public:
    Fenwick_Tree(const std::vector<int> &values)
    {
        tree = std::vector<int>{0};
        tree.insert(tree.begin() + 1, values.begin(), values.end());

        for (int i = 1; i < tree.size(); i++)
        {
            int child_index = i + lsb(i);
            if (child_index < tree.size())
            {
                tree[child_index] += tree[i];
            }
        }
    }

    // get the prefix sum from [0, index] of A
    int query(int index)
    {
        index++;
        int sum = 0;
        while (index > 0)
        {
            sum += tree[index];
            index -= lsb(index);
        }

        return sum;
    }

    // get the sum of [start_index, end_index] of A
    int query(const int &start_index, const int &end_index)
    {
        return this->query(end_index) - this->query(start_index - 1);
    }

    // update the value of A[index], note that the change in value must be given here as input, i.e. A_new[index] -
    // A_old[index]
    void update(int index, const int &change)
    {
        index++;
        while (index < tree.size())
        {
            tree[index] += change;
            index += lsb(index);
        }
    }

  private:
    std::vector<int> tree;
};

std::vector<int> solve_problem(const std::vector<int> &problem)
{
    // reminder that in the input phase, all elements were decremented by one (so it is an array of the elements
    // 0,..,n-1)
    // initially all elements are present, if we sort one, then we will pretend that we just removed it
    std::vector<int> element_present(problem.size(), 1);
    Fenwick_Tree fenwick_tree = Fenwick_Tree(element_present);

    std::vector<int> element_position(problem.size());
    for (int i = 0; i < problem.size(); i++)
    {
        element_position[problem[i]] = i;
    }

    // as in the turbo-sort description alternate between putting the lowest to its correct position and the highest to
    // its correct position with swaps
    int low = 0;
    int high = problem.size() - 1;
    std::vector<int> output;
    output.reserve(problem.size());
    while (low <= high)
    {
        int index_low = element_position[low];
        // get the number of elements that have not been moved yet between [0, index_low)
        int num_elements_before = fenwick_tree.query(index_low - 1);
        output.push_back(num_elements_before);
        // this element is now removed
        fenwick_tree.update(index_low, -1);
        low++;

        if (low > high)
        {
            return output;
        }

        int index_high = element_position[high];
        // get the number of elements that have not been moved yet between (index_high, n)
        int num_elements_after = fenwick_tree.query(index_high + 1, problem.size() - 1);
        output.push_back(num_elements_after);
        // this element is now removed
        fenwick_tree.update(index_high, -1);
        high--;
    }

    return output;
}