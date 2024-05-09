// Authors: Marc Gröling

#ifndef graph
#define graph

#include <stdexcept>
#include <vector>

class Graph
{
  public:
    virtual int getNumVertices() const = 0;

    // get the indices and distances of all vertices that are adjacent to the given vertex
    virtual std::vector<std::pair<int, double>> getNeighbours(const int &vertex) const = 0;

    // creates an edge of weight between vertex1 and vertex2
    virtual void addEdge(const int &vertex1, const int &vertex2, const double &weight, const bool &bidirectional) = 0;

    // increases the weight of an existing edge
    virtual void changeEdge(const int &vertex1, const int &vertex2, const double &increase_weight_by) = 0;
};

class AdjacencyListGraph : public Graph
{
  public:
    std::vector<std::vector<std::pair<int, double>>> adjacencylist;

    AdjacencyListGraph()
    {
    }

    AdjacencyListGraph(int numVertices)
    {
        adjacencylist.resize(numVertices);
    }

    int getNumVertices() const override
    {
        return adjacencylist.size();
    }

    std::vector<std::pair<int, double>> getNeighbours(const int &vertex) const override
    {
        if (vertex < 0 || vertex >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertex must be >= 0 and < numVertices");
        }
        return adjacencylist[vertex];
    }

    void addEdge(const int &vertex1, const int &vertex2, const double &weight, const bool &bidirectional) override
    {
        // assumes that the edge didn't exist before
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= adjacencylist.size() || vertex2 >= adjacencylist.size())
        {
            throw std::invalid_argument("Vertices must be >= 0 and < numVertices");
        }
        adjacencylist[vertex1].emplace_back(vertex2, weight);
        if (bidirectional)
        {
            adjacencylist[vertex2].emplace_back(vertex1, weight);
        }
    }

    void changeEdge(const int &vertex1, const int &vertex2, const double &increase_weight_by)
    {
        for (int i = 0; i < adjacencylist[vertex1].size(); i++)
        {
            if (adjacencylist[vertex1][i].first == vertex2)
            {
                adjacencylist[vertex1][i] = {vertex2, adjacencylist[vertex1][i].second + increase_weight_by};
                break;
            }
        }
    }
};

#endif