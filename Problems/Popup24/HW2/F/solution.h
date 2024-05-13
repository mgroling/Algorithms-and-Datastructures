/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

These days, you can do all sorts of things online. For example, you can use various websites to make virtual friends.
For some people, growing their social network (their friends, their friends’ friends, their friends’ friends’ friends,
and so on), has become an addictive hobby. Just as some people collect stamps, other people collect virtual friends.

Your task is to observe the interactions on such a website and keep track of the size of each person’s network.

Assume that every friendship is mutual. If Fred is Barney’s friend, then Barney is also Fred’s friend.

----------------------------------------------------- INPUT -----------------------------------------------------

The first line of input contains one integer specifying the number of test cases to follow. Each test case begins with a
line containing a positive integer F, the number of friendships formed. Each of the following F lines contains the names
of two people who have just become friends, separated by a space. A name is a string of 1 to 6 letters (uppercase or
lowercase). The sum of F over all test cases in the file is at most 100 000.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Whenever a friendship is formed, print a line containing one integer, the number of people in the social network of the
two people who have just become friends.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
1
3
Fred Barney
Barney Betty
Betty Wilma

Sample Output:
2
3
4

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can use the disjoint-sets/union-find datastructure. This works by having nodes in a tree structure. If we want to
know if two nodes are in the same set, we can get both their roots and check if they are the same. Otherwise, we merge
the two sets (trees). We keep track of the size of a set (tree).

*/

#include <string>
#include <unordered_map>
#include <vector>

struct Node
{
    Node *parent = NULL;
    int size = 1;
};

Node *get_root(Node *cur)
{
    std::vector<Node *> to_change;
    while (cur->parent != NULL)
    {
        to_change.push_back(cur);
        cur = cur->parent;
    }

    // also set the root of all nodes visited to cur (so that future get_root operations will be faster)
    for (Node *node : to_change)
    {
        node->parent = cur;
    }

    return cur;
}

void solve_test_case(const std::vector<std::pair<std::string, std::string>> &test_case, std::vector<int> &output)
{
    std::unordered_map<std::string, Node *> friend_map;

    for (const std::pair<std::string, std::string> friends : test_case)
    {
        // check if the friends names already have a node
        auto ptr1 = friend_map.find(friends.first);
        Node *first;
        if (ptr1 != friend_map.end())
        {
            first = ptr1->second;
        }
        else
        {
            first = new Node();
            friend_map[friends.first] = first;
        }

        auto ptr2 = friend_map.find(friends.second);
        Node *second;
        if (ptr2 != friend_map.end())
        {
            second = ptr2->second;
        }
        else
        {
            second = new Node();
            friend_map[friends.second] = second;
        }

        Node *root1 = get_root(first);
        Node *root2 = get_root(second);

        // they were friends anyway (through others), size of the friend network doesn't increase
        if (root1 == root2)
        {
            output.push_back(root1->size);
        }
        // they weren't friends at all, size of the friend network increases
        else
        {
            if (root1->size < root2->size)
            {
                root1->parent = root2;
                root2->size += root1->size;
                output.push_back(root2->size);
            }
            else
            {
                root2->parent = root1;
                root1->size += root2->size;
                output.push_back(root1->size);
            }
        }
    }
}

std::vector<int> solve_problem(std::vector<std::vector<std::pair<std::string, std::string>>> &input)
{
    std::vector<int> output;

    for (const std::vector<std::pair<std::string, std::string>> &test_case : input)
    {
        solve_test_case(test_case, output);
    }

    return output;
}