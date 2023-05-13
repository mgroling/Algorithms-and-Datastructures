#include <cassert>
#include <functional>
#include <iostream>

#include "../Datastructures/heap.h"

int main() {
    BinaryHeap<int> h = BinaryHeap<int>(std::less<int>{});

    // Insert 5 unsorted numbers into the heap
    h.insert(50);
    h.insert(10);
    h.insert(30);
    h.insert(90);
    h.insert(20);

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Extract the first 3 numbers from the heap
    assert(h.extract() == 10);
    assert(h.extract() == 20);
    assert(h.extract() == 30);

    // Verify that the heap now has size 2
    assert(h.size() == 2);

    // Insert 2 more unsorted numbers into the heap
    h.insert(40);
    h.insert(60);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 40);
    assert(h.extract() == 50);
    assert(h.extract() == 60);

    // Verify that the heap now has size 1
    assert(h.size() == 1);

    // Insert 3 more unsorted numbers into the heap
    h.insert(80);
    h.insert(70);
    h.insert(100);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 70);
    assert(h.extract() == 80);
    assert(h.extract() == 90);
    assert(h.extract() == 100);

    // Verify that the heap is now empty
    assert(h.empty());

    return 0;
}