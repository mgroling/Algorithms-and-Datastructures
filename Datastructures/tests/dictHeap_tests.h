#include <cassert>

#include "../dictHeap.h"

void dictHeap_int_less(DictHeap<int>& h) {
    // Insert 5 unsorted numbers into the heap
    h.insert(50, 15);
    h.insert(10, 10);
    h.insert(30, 80);
    h.insert(90, 40);
    h.insert(20, 20);

    // Change some keys
    h.changeKey(50, 50);
    h.changeKey(30, 30);

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Extract the first 3 numbers from the heap
    assert(h.extract() == 10);
    assert(h.extract() == 20);
    assert(h.extract() == 30);

    // Change another key
    h.changeKey(90, 90);

    // Verify that the heap now has size 2
    assert(h.size() == 2);

    // Insert 2 more unsorted numbers into the heap
    h.insert(40, 40);
    h.insert(60, 60);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 40);
    assert(h.extract() == 50);
    assert(h.extract() == 60);

    // Verify that the heap now has size 1
    assert(h.size() == 1);

    // Insert 3 more unsorted numbers into the heap
    h.insert(80, 80);
    h.insert(70, 70);
    h.insert(100, 100);

    // Change priorities of keys to other values
    h.changeKey(70, 200);
    h.changeKey(100, 10);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 100);
    assert(h.extract() == 80);
    assert(h.extract() == 90);
    assert(h.extract() == 70);

    // Verify that the heap is now empty
    assert(h.empty());
}

void dictHeap_int_greater(DictHeap<int>& h) {
    // Insert 5 unsorted numbers into the heap
    h.insert(50, 200);
    h.insert(10, 10);
    h.insert(30, 0);
    h.insert(90, 90);
    h.insert(20, 0);

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Change some keys
    h.changeKey(50, 50);
    h.changeKey(30, 30);

    // Extract the first 3 numbers from the heap
    assert(h.extract() == 90);
    assert(h.extract() == 50);
    assert(h.extract() == 30);

    // Change another key
    h.changeKey(20, 20);

    // Verify that the heap now has size 2
    assert(h.size() == 2);

    // Insert 2 more unsorted numbers into the heap
    h.insert(40, 40);
    h.insert(60, 60);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 60);
    assert(h.extract() == 40);
    assert(h.extract() == 20);

    // Verify that the heap now has size 1
    assert(h.size() == 1);

    // Insert 3 more unsorted numbers into the heap
    h.insert(80, 80);
    h.insert(70, 70);
    h.insert(100, 100);

    // Change priorities of keys to other values
    h.changeKey(70, 200);
    h.changeKey(100, 0);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 70);
    assert(h.extract() == 80);
    assert(h.extract() == 10);
    assert(h.extract() == 100);

    // Verify that the heap is now empty
    assert(h.empty());
}

struct MyStructDictHeap {
    int x;
    int y;

    MyStructDictHeap(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const MyStructDictHeap& other) const {
        return x == other.x & y == other.y;
    }

    MyStructDictHeap& operator=(const MyStructDictHeap& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

namespace std {

template <>
struct hash<MyStructDictHeap> {
    std::size_t operator()(const MyStructDictHeap& s) const noexcept {
        return std::hash<int>()(s.x) ^ std::hash<int>()(s.y);
    }
};

}  // namespace std

void dictHeap_custom_less(DictHeap<MyStructDictHeap>& h) {
    // Insert 5 unsorted structs into the heap
    h.insert(MyStructDictHeap(10, 5), 35);
    h.insert(MyStructDictHeap(0, 40), 40);
    h.insert(MyStructDictHeap(4, 20), 32);
    h.insert(MyStructDictHeap(15, 0), 45);
    h.insert(MyStructDictHeap(9, 7), 34);

    // Verify that the heap now has size 5
    assert(h.size() == 5);

    // Extract the first 2 structs from the heap
    assert(h.extract() == MyStructDictHeap(4, 20));
    assert(h.extract() == MyStructDictHeap(9, 7));

    // Increase one key and decrease another
    h.changeKey(MyStructDictHeap(15, 0), 30);
    h.changeKey(MyStructDictHeap(10, 5), 50);

    assert(h.extract() == MyStructDictHeap(15, 0));
    assert(h.extract() == MyStructDictHeap(0, 40));
    assert(h.extract() == MyStructDictHeap(10, 5));

    // Verify that the heap is now empty
    assert(h.empty());
}

void test_binaryDictHeap_int_less() {
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    dictHeap_int_less(h);
}

void test_binaryDictHeap_int_greater() {
    BinaryDictHeap<int> h = BinaryDictHeap<int>(false);
    dictHeap_int_greater(h);
}

void test_binaryDictHeap_custom_less() {
    BinaryDictHeap<MyStructDictHeap> h = BinaryDictHeap<MyStructDictHeap>(true);
    dictHeap_custom_less(h);
}