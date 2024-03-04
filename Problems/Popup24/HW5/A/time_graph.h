// Authors: Marc Gröling

#ifndef time_graph
#define time_graph

#include <stdexcept>
#include <tuple>
#include <vector>

class TimeGraph
{
  public:
    virtual int getNumVertices() const = 0;

    // get the indices and distances of all vertices that are adjacent to the given vertex (also time information)
    virtual std::vector<std::tuple<int, int, std::vector<int>>> getNeighbours(const int &vertex) const = 0;

    // creates an edge of weight between vertex1 and vertex2
    virtual void addEdge(const int &vertex1, const int &vertex2, const int &weight, const std::vector<int> &time_info,
                         const bool &bidirectional) = 0;
};

class AdjacencyListTimeGraph : public TimeGraph
{
  public:
    std::vector<std::vector<std::tuple<int, int, std::vector<int>>>> adjacencylist;

    AdjacencyListTimeGraph(int numVertices)
    {
        adjacencylist.resize(numVertices);
    }

    int getNumVertices() const override
    {
        return adjacencylist.size();
    }

    std::vector<std::tuple<int, int, std::vector<int>>> getNeighbours(const int &vertex) const override
    {
        if (vertex < 0 || vertex >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertex must be >= 0 and < numVertices");
        }
        return adjacencylist[vertex];
    }

    void addEdge(const int &vertex1, const int &vertex2, const int &weight, const std::vector<int> &time_info,
                 const bool &bidirectional) override
    {
        // assumes that the edge didn't exist before
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= adjacencylist.size() || vertex2 >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertices must be >= 0 and < numVertices");
        }
        adjacencylist[vertex1].emplace_back(vertex2, weight, time_info);
        if (bidirectional)
        {
            adjacencylist[vertex2].emplace_back(vertex1, weight, time_info);
        }
    }
};

#endif