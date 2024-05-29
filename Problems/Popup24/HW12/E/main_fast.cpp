#include <array>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

struct Trie_Node
{
    std::unordered_map<char, int> children{};
    bool multiple_words_underneath = false;
};

// precompute factorial values for 1..27 (a node has a maximum of 27 children)
constexpr std::array<uint64_t, 27> compute_factorial(const uint64_t &modulus)
{
    std::array<uint64_t, 27> factorial{};
    factorial[0] = 1;

    for (int i = 1; i < factorial.size(); ++i)
    {
        factorial[i] = (factorial[i - 1] * (i + 1)) % modulus;
    }

    return factorial;
}

int main()
{
    constexpr uint64_t modulus = 1000000007;
    std::vector<Trie_Node> nodes;
    nodes.reserve(9000000);
    nodes.emplace_back();
    int num_names;
    std::cin >> num_names;
    std::cin.ignore();
    // construct a trie with all the given words of the input
    for (int i = 0; i < num_names; ++i)
    {
        std::string name;
        std::getline(std::cin, name);
        int cur = 0;
        for (const char &letter : name)
        {
            // cur already has at least one child and we go down this path again => it will have multiple descendants
            if (!nodes[cur].children.empty())
            {
                nodes[cur].multiple_words_underneath = true;
            }

            // child with letter doesn't exist
            if (nodes[cur].children.find(letter) == nodes[cur].children.end())
            {
                nodes.emplace_back();
                nodes[cur].children[letter] = nodes.size() - 1;
            }

            cur = nodes[cur].children[letter];
        }

        if (!nodes[cur].children.empty())
        {
            nodes[cur].multiple_words_underneath = true;
        }
        // if it is the end of a word, also add an asterisk to the end (to mark that this is a word)
        nodes.emplace_back();
        nodes[cur].children['*'] = nodes.size() - 1;
    }

    // compute first 27 factorial numbers (at compile time)
    constexpr std::array<uint64_t, 27> factorial = compute_factorial(modulus);

    uint64_t num_combinations = 1;
    std::stack<int> stack;
    stack.push(0);

    while (!stack.empty())
    {
        int cur = stack.top();
        stack.pop();

        if (!nodes[cur].children.empty())
        {
            // if there are multiple children, then there are k! (children.size() = k) many ways to arrange these
            num_combinations = (num_combinations * factorial[nodes[cur].children.size() - 1]) % modulus;

            for (const std::pair<char, int> &child : nodes[cur].children)
            {
                // only need to continue going down this path if multiple words will end there
                if (nodes[child.second].multiple_words_underneath)
                {
                    stack.push(child.second);
                }
            }
        }
    }

    std::cout << num_combinations << '\n';

    return 0;
}