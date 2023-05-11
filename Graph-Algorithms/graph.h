#include "vector"
#include "array"

class AbstractGraph
{
public:
    virtual std::vector<int> getNeighbours(const int &node) const = 0;
};

template <int numNodes>
class AdjacencyMatrixGraph : public AbstractGraph
{
public:
    std::array<bool, numNodes * numNodes> matrix;

    std::vector<int> getNeighbours(const int &node) const override
    {
        std::vector<int> neighbours;
        // init pointer to the first entry of the given node
        const bool *ptr = matrix.begin() + node * numNodes;

        for (int i = 0; i < numNodes; i++)
        {
            if (*(ptr))
            {
                neighbours.push_back(i);
            }
            ptr++;
        }
        return neighbours;
    }
};