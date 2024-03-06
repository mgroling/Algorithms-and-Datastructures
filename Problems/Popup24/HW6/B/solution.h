/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

A catenym is a pair of words separated by a period such that the last letter of the first word is the same as the first
letter of the second. For example, the following are catenyms:

dog.gopher
gopher.rat
rat.tiger
aloha.aloha
arachnid.dog

A compound catenym is a sequence of three or more words separated by periods such that each adjacent pair of words forms
a catenym. For example,

aloha.aloha.arachnid.dog.gopher.rat.tiger

----------------------------------------------------- INPUT -----------------------------------------------------

Given a dictionary of lower case words, you are to find a compound catenym that contains each of the words exactly once.
The first line of standard input contains t, the number of test cases. Each test case begins with 3 <= n <= 1000 – the
number of words in the dictionary. n distinct dictionary words follow; each word is a string of between 1 and 20
lowercase letters on a line by itself.

----------------------------------------------------- OUTPUT -----------------------------------------------------

For each test case, output a line giving the lexicographically smallest compound catenym that contains each dictionary
word exactly once. Output “***” if there is no solution.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
2
6
aloha
arachnid
dog
gopher
rat
tiger
3
oak
maple
elm

Sample Output:
aloha.arachnid.dog.gopher.rat.tiger
***

----------------------------------------------------- SOLUTION -----------------------------------------------------

We can view each word as a directed edge in a graph. The vertices are the letters a-z. A word goes from the vertex of
its first letter to the vertex of its last letter. Now we just need to find a eulerian path.

My implementation of Hierholzer's algorithm always takes the last available edge first, so we need to add them in
reverse lexicographic order. Also, the path starts (in case there is no eulerian cycle) from the last vertex with an
outgoing edge, so we need to have the vertices numbered in reverse lexicographic order as well.

*/

#include "eulerian_path.h"
#include "graph.h"
#include "kattisio.h"

#include <algorithm>
#include <tuple>
#include <vector>

// maps a -> 25, b -> 24, .., z -> 0
int charToInt(const char &letter)
{
    return 25 - (letter - 'a');
}

std::string solve_test_case(Test_case &test_case)
{
    int num_letters = 26;
    // sort all words lexicographically
    std::sort(test_case.words.begin(), test_case.words.end());

    // create graph
    AdjacencyListGraph g = AdjacencyListGraph(num_letters);

    // go through words in descending lexicographic order (to add edges in correct order)
    for (int i = test_case.words.size() - 1; i >= 0; i--)
    {
        g.addEdge(charToInt(test_case.words[i][0]), charToInt(test_case.words[i].back()), 1, false);
    }

    std::vector<int> path = hierholzersAlgorithm(g);

    // no eulerian path
    if (!path.size())
    {
        return "***\n";
    }

    // create a mapping from each pair of vertices to each word, so that the lexicographic smallest word is last
    std::vector<std::vector<std::vector<std::string>>> word_mappings(
        num_letters, std::vector<std::vector<std::string>>(num_letters, std::vector<std::string>{}));
    for (int i = test_case.words.size() - 1; i >= 0; i--)
    {
        word_mappings[charToInt(test_case.words[i][0])][charToInt(test_case.words[i].back())].push_back(
            test_case.words[i]);
    }

    std::string output = "";

    // we only get the vertices in the eulerian path, now we have to use the "best" (lexiographic smallest edge/word)
    for (int i = 0; i < path.size() - 1; i++)
    {
        output += word_mappings[path[i]][path[i + 1]].back();
        word_mappings[path[i]][path[i + 1]].pop_back();
        if (i != path.size() - 2)
        {
            output += '.';
        }
    }

    return output + '\n';
}

std::string solve_problem(std::vector<Test_case> &test_cases)
{
    std::string output = "";

    for (Test_case &test_case : test_cases)
    {
        output += solve_test_case(test_case);
    }

    return output;
}