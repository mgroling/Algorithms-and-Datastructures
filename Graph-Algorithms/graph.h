#include "array"
#include "vector"

class AbstractGraph {
   public:
    // get the index of all vertices that are adjacent to the given vertex
    virtual std::vector<int> getNeighbours(const int &vertex) const = 0;
};

template <int numVertices>
// Graph Class that uses an adjacency matrix to keep track of edges
// matrix[i * (numVertices) + j] == 1 means that there is an edge going from vertex i to vertex j
class AdjacencyMatrixGraph : public AbstractGraph {
   public:
    std::array<bool, numVertices * numVertices> matrix;

    AdjacencyMatrixGraph(std::array<bool, numVertices * numVertices> adjacencyMatrix) {
        matrix = adjacencyMatrix;
    }

    std::vector<int> getNeighbours(const int &vertex) const override {
        std::vector<int> neighbours;
        // init pointer to the first edge of the given vertex
        const bool *ptr = matrix.begin() + vertex * numVertices;

        for (int i = 0; i < numVertices; i++) {
            if (*ptr++) {
                neighbours.push_back(i);
            }
        }
        return neighbours;
    }
};