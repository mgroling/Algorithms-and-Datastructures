/*
----------------------------------------------------- PROBLEM -----------------------------------------------------


----------------------------------------------------- INPUT -----------------------------------------------------


----------------------------------------------------- OUTPUT -----------------------------------------------------


----------------------------------------------------- EXAMPLE -----------------------------------------------------


----------------------------------------------------- SOLUTION -----------------------------------------------------


*/

#include <array>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

constexpr uint64_t modulus = 1000000007;

void populate_factorial(std::array<uint64_t, 27> &factorial)
{
    // precompute factorial values for 1..27 (a node has a maximum of 27 children)
    factorial[0] = 1;

    for (int i = 1; i < factorial.size(); i++)
    {
        factorial[i] = (factorial[i - 1] * (i + 1)) % modulus;
    }
}

class TrieNode
{
  public:
    std::unordered_map<char, TrieNode *> children;
    bool multiple_nodes = false;
};

void delete_trie(TrieNode *root)
{
    for (const std::pair<char, TrieNode *> &child : root->children)
    {
        delete_trie(child.second);
    }
    delete root;
}

uint64_t compute_num_combinations(TrieNode *root, const std::array<uint64_t, 27> &factorial)
{
    uint64_t num_combinations = 1;

    std::stack<TrieNode *> nodes;
    nodes.push(root);

    while (nodes.size())
    {
        TrieNode *cur = nodes.top();
        nodes.pop();

        if (cur->children.size())
        {
            // if there are multiple children, then there are k! (children.size() = k) many ways to arrange these
            num_combinations = (num_combinations * factorial[cur->children.size() - 1]) % modulus;

            for (const std::pair<char, TrieNode *> &child : cur->children)
            {
                if (child.second->multiple_nodes)
                {
                    nodes.push(child.second);
                }
            }
        }
    }

    return num_combinations;
}

uint64_t solve_problem(std::vector<std::string> &input)
{
    std::array<uint64_t, 27> factorial;
    populate_factorial(factorial);

    TrieNode *root = new TrieNode();

    // construct a trie with all the given words of the input
    for (const std::string &word : input)
    {
        TrieNode *current = root;
        for (const char &letter : word)
        {
            // current already has at least one child and we go down this path again => it will have multiple
            // descendants
            if (current->children.size())
            {
                current->multiple_nodes = true;
            }
            // child with letter doesn't exist
            if (current->children.find(letter) == current->children.end())
            {
                current->children[letter] = new TrieNode();
            }

            current = current->children[letter];
        }

        if (current->children.size())
        {
            current->multiple_nodes = true;
        }
        // if it is the end of a word, also add an asterisk to the end (to mark that this is a word)
        current->children['*'] = new TrieNode();
    }

    uint64_t num_combinations = compute_num_combinations(root, factorial);

    // delete_trie(root);

    return num_combinations;
}