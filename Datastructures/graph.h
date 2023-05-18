#ifndef graph
#define graph

#include "array"
#include "tuple"
#include "vector"

class Graph {
   public:
    virtual int getNumVertices() const = 0;

    virtual double getCost(const int &vertex1, const int &vertex2) const = 0;

    // get the indices of all vertices that are adjacent to the given vertex
    virtual std::tuple<std::vector<int>, std::vector<double>> getNeighbours(const int &vertex) const = 0;

    // creates an edge of weight between vertex1 and vertex2
    virtual void addEdge(const int &vertex1, const int &vertex2, const double &weight, const bool &bidirectional) = 0;
};

template <int numVertices>
// Graph Class that uses an adjacency matrix to keep track of edges
// matrix[i * (numVertices) + j] == 0 means that there is no edge going from vertex i to vertex j, otherwise there is one with the value as weight
class AdjacencyMatrixGraph : public Graph {
   public:
    std::array<double, numVertices * numVertices> matrix;

    AdjacencyMatrixGraph() {
        matrix = {0};
    }

    AdjacencyMatrixGraph(std::array<double, numVertices * numVertices> adjacencyMatrix) {
        matrix = adjacencyMatrix;
    }

    int getNumVertices() const override {
        return numVertices;
    }

    double getCost(const int &vertex1, const int &vertex2) const override {
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= numVertices || vertex2 >= numVertices) {
            throw std::invalid_argument("Vertices must be >= 0 and < numVertices");
        }
        return matrix[vertex1 * numVertices + vertex2];
    }

    std::tuple<std::vector<int>, std::vector<double>> getNeighbours(const int &vertex) const override {
        if (vertex < 0 || vertex >= numVertices) {
            throw std::invalid_argument("Vertex must be >= 0 and < numVertices");
        }
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

    void addEdge(const int &vertex1, const int &vertex2, const double &weight, const bool &bidirectional) override {
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= numVertices || vertex2 >= numVertices) {
            throw std::invalid_argument("Vertices must be >= 0 and < numVertices");
        }
        if (vertex1 == vertex2) {
            throw std::invalid_argument("Vertices must not be the same");
        }
        matrix[vertex1 * numVertices + vertex2] = weight;
        if (bidirectional) {
            matrix[vertex2 * numVertices + vertex1] = weight;
        }
    }
};

#endif