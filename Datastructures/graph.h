#ifndef graph
#define graph

#include "array"
#include "tuple"
#include "vector"

class Graph {
   public:
    // get the indices of all vertices that are adjacent to the given vertex
    virtual std::tuple<std::vector<int>, std::vector<double>> getNeighbours(const int &vertex) const = 0;
};

template <int numVertices>
// Graph Class that uses an adjacency matrix to keep track of edges
// matrix[i * (numVertices) + j] == 0 means that there is no edge going from vertex i to vertex j, otherwise there is one with the value as weight
class AdjacencyMatrixGraph : public Graph {
   public:
    std::array<double, numVertices * numVertices> matrix;

    AdjacencyMatrixGraph(std::array<double, numVertices * numVertices> adjacencyMatrix) {
        matrix = adjacencyMatrix;
    }

    std::tuple<std::vector<int>, std::vector<double>> getNeighbours(const int &vertex) const override {
        std::vector<int> neighbours;
        std::vector<double> distances;
        // init pointer to the first edge of the given vertex
        const double *ptr = matrix.begin() + vertex * numVertices;

        for (int i = 0; i < numVertices; i++) {
            double weight = *ptr++;
            if (weight) {
                neighbours.push_back(i);
                distances.push_back(weight);
            }
        }
        return std::tuple<std::vector<int>, std::vector<double>>{neighbours, distances};
    }
};

#endif