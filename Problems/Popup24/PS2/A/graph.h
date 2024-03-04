// Authors: Marc Gröling

#ifndef graph
#define graph

#include <stdexcept>
#include <tuple>
#include <vector>

class Graph
{
  public:
    virtual int getNumVertices() const = 0;

    // get the indices and distances of all vertices that are adjacent to the given vertex
    virtual std::vector<std::tuple<int, int, double, int>> getNeighbours(const int &vertex) const = 0;

    // creates an edge of weight between vertex1 and vertex2
    virtual void addEdge(const int &vertex1, const int &vertex2, const int &capacity, const double &cost,
                         const int &flow) = 0;
};

class AdjacencyListGraph : public Graph
{
  public:
    std::vector<std::vector<std::tuple<int, int, double, int>>> adjacencylist;

    AdjacencyListGraph(int numVertices)
    {
        adjacencylist.resize(numVertices);
    }

    int getNumVertices() const override
    {
        return adjacencylist.size();
    }

    std::vector<std::tuple<int, int, double, int>> getNeighbours(const int &vertex) const override
    {
        if (vertex < 0 || vertex >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertex must be >= 0 and < numVertices");
        }
        return adjacencylist[vertex];
    }

    void addEdge(const int &vertex1, const int &vertex2, const int &capacity, const double &cost,
                 const int &flow) override
    {
        // assumes that the edge didn't exist before
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= adjacencylist.size() || vertex2 >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertices must be >= 0 and < numVertices");
        }
        adjacencylist[vertex1].emplace_back(vertex2, capacity, cost, flow);
    }

    double changeEdge(const int &vertex1, const int &vertex2, const int &flow)
    {
        for (int j = 0; j < adjacencylist[vertex1].size(); j++)
        {
            if (std::get<0>(adjacencylist[vertex1][j]) == vertex2)
            {
                adjacencylist[vertex1][j] = std::tuple<int, int, double, int>{
                    vertex2, std::get<1>(adjacencylist[vertex1][j]), std::get<2>(adjacencylist[vertex1][j]), flow};
                return std::get<2>(adjacencylist[vertex1][j]);
            }
        }
        return -1;
    }
};

#endif