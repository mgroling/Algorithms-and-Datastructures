#include <functional>
#include <iostream>

#include "../Datastructures/heap.h"
#include "graph.h"

int main() {
    // AdjacencyMatrixGraph g = AdjacencyMatrixGraph<3>(std::array<bool, 9>{true, false, true, false, true, false, false, true, true});

    // std::vector<int> neighbours = g.getNeighbours(1);
    // for (int i = 0; i < neighbours.size(); i++) {
    //     std::cout << neighbours[i] << "\n";
    // }

    BinaryHeap h = BinaryHeap<int>(std::less<int>{});

    h.insert(5);
    h.insert(4);
    h.insert(3);
    h.insert(7);
    h.insert(11);
    h.insert(1);
    h.print();
    std::cout << h.extract() << "\n";
    std::cout << h.extract() << "\n";
    std::cout << h.extract() << "\n";
    std::cout << h.extract() << "\n";
    std::cout << h.extract() << "\n";
    std::cout << h.extract() << "\n";

    return 0;
}