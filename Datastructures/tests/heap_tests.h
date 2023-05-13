#include <cassert>
#include <functional>

#include "../heap.h"

void test_binaryHeap_normal_operation_int_less() {
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
}

void test_binaryHeap_normal_operation_int_greater() {
    BinaryHeap<int> h = BinaryHeap<int>(std::greater<int>{});
    // Insert 5 unsorted numbers into the heap
    h.insert(50);
    h.insert(10);
    h.insert(30);
    h.insert(90);
    h.insert(20);

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Extract the first 3 numbers from the heap
    assert(h.extract() == 90);
    assert(h.extract() == 50);
    assert(h.extract() == 30);

    // Verify that the heap now has size 2
    assert(h.size() == 2);

    // Insert 2 more unsorted numbers into the heap
    h.insert(40);
    h.insert(60);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 60);
    assert(h.extract() == 40);
    assert(h.extract() == 20);

    // Verify that the heap now has size 1
    assert(h.size() == 1);

    // Insert 3 more unsorted numbers into the heap
    h.insert(80);
    h.insert(70);
    h.insert(100);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 100);
    assert(h.extract() == 80);
    assert(h.extract() == 70);
    assert(h.extract() == 10);

    // Verify that the heap is now empty
    assert(h.empty());
}

struct MyStruct {
    int x;
    int y;

    MyStruct(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator<(const MyStruct& other) const {
        return x * 3 + y < other.x * 3 + other.y;
    }

    bool operator==(const MyStruct& other) const {
        return x == other.x & y == other.y;
    }

    MyStruct& operator=(const MyStruct& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

void test_binaryHeap_normal_operation_custom_less() {
    BinaryHeap<MyStruct> h = BinaryHeap<MyStruct>(std::less<MyStruct>{});
    // Insert 5 unsorted structs into the heap
    h.insert(MyStruct(10, 5));  // 35
    h.insert(MyStruct(0, 40));  // 40
    h.insert(MyStruct(4, 20));  // 32
    h.insert(MyStruct(15, 0));  // 45
    h.insert(MyStruct(9, 7));   // 34

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Extract the 5 structs from the heap
    assert(h.extract() == MyStruct(4, 20));
    assert(h.extract() == MyStruct(9, 7));
    assert(h.extract() == MyStruct(10, 5));
    assert(h.extract() == MyStruct(0, 40));
    assert(h.extract() == MyStruct(15, 0));

    // Verify that the heap is now empty
    assert(h.empty());
}