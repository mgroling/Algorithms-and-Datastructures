#include <algorithm>
#include <cassert>

#include "../dictHeap.h"
#include "array"

void dictHeap_int_less(DictHeap<int> &h)
{
    // Insert 5 unsorted numbers into the heap
    h.insert(50, 65);
    h.insert(10, 10);
    h.insert(30, 80);
    h.insert(90, 140);
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
    h.insert(70, 300);
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

void dictHeap_int_greater(DictHeap<int> &h)
{
    // Insert 5 unsorted numbers into the heap
    h.insert(50, 2);
    h.insert(10, 10);
    h.insert(30, 0);
    h.insert(90, 90);
    h.insert(20, 15);

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
    h.changeKey(100, 150);

    // Verify that the heap now has size 4
    assert(h.size() == 4);

    // 10, 10
    // 80, 80

    // Extract the next 3 numbers from the heap
    assert(h.extract() == 70);
    assert(h.extract() == 100);
    assert(h.extract() == 80);
    assert(h.extract() == 10);

    // Verify that the heap is now empty
    assert(h.empty());
}

struct MyStructDictHeap
{
    int x;
    int y;

    MyStructDictHeap()
    {
    }

    MyStructDictHeap(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const MyStructDictHeap &other) const
    {
        return x == other.x & y == other.y;
    }

    MyStructDictHeap &operator=(const MyStructDictHeap &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

namespace std
{

template <> struct hash<MyStructDictHeap>
{
    std::size_t operator()(const MyStructDictHeap &s) const noexcept
    {
        return std::hash<int>()(s.x) ^ std::hash<int>()(s.y);
    }
};

} // namespace std

void dictHeap_custom_less(DictHeap<MyStructDictHeap> &h)
{
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

    // Decrease two keys
    h.changeKey(MyStructDictHeap(15, 0), 30);
    h.changeKey(MyStructDictHeap(10, 5), 0);

    assert(h.extract() == MyStructDictHeap(10, 5));
    assert(h.extract() == MyStructDictHeap(15, 0));
    assert(h.extract() == MyStructDictHeap(0, 40));

    // Verify that the heap is now empty
    assert(h.empty());
}

void dictHeap_int_less_increaseKey(DictHeap<int> &h)
{
    h.insert(10, 0);
    h.insert(5, 5);
    h.insert(15, 15);
    h.insert(20, 20);
    h.insert(0, 0);

    h.changeKey(10, 10);
    h.changeKey(5, 30);
    h.changeKey(0, 25);

    assert(h.extract() == 10);
    assert(h.extract() == 15);
    assert(h.extract() == 20);
    assert(h.extract() == 0);
    assert(h.extract() == 5);

    assert(h.empty());
}

void dictHeap_int_less_many(DictHeap<int> &h)
{
    std::array<int, 105> numbers = {
        57, 23, 81, 96, 102, 4,  68, 35, 92, 7,  10, 29, 62, 17, 52, 86, 103, 42,  75, 14,  61, 39, 55,  31, 3,  94, 72,
        50, 76, 1,  87, 45,  98, 9,  70, 59, 30, 12, 19, 83, 38, 48, 28, 93,  101, 69, 41,  85, 66, 22,  99, 32, 79, 8,
        97, 18, 26, 91, 104, 43, 15, 64, 24, 73, 47, 2,  80, 11, 37, 78, 13,  67,  20, 105, 54, 88, 6,   89, 21, 58, 84,
        27, 95, 46, 16, 90,  56, 33, 71, 49, 77, 34, 63, 25, 74, 5,  40, 82,  36,  60, 51,  65, 44, 100, 53};

    std::array<int, 6> first_to_remove = {23, 4, 1, 3, 2, 5};
    std::array<int, 99> remaining = {
        57, 81, 96, 102, 68,  35, 92, 7,  10, 29, 62, 17, 52, 86, 103, 42,  75, 14, 61,  39, 55, 31, 94,  72, 50,
        76, 87, 45, 98,  9,   70, 59, 30, 12, 19, 83, 38, 48, 28, 93,  101, 69, 41, 85,  66, 22, 99, 32,  79, 8,
        97, 18, 26, 91,  104, 43, 15, 64, 24, 73, 47, 80, 11, 37, 78,  13,  67, 20, 105, 54, 88, 6,  89,  21, 58,
        84, 27, 95, 46,  16,  90, 56, 33, 71, 49, 77, 34, 63, 25, 74,  40,  82, 36, 60,  51, 65, 44, 100, 53};
    std::sort(std::begin(remaining), std::end(remaining));

    // insert 5 numbers, then extract 1, then add 10, then extract 1, ...
    int cur_index = 0;
    for (int i = 1; i < 7; i++)
    {
        // insert numbers
        for (int j = 0; j < i * 5; j++)
        {
            h.insert(numbers[cur_index], numbers[cur_index]);
            cur_index++;
        }

        assert(h.extract() == first_to_remove[i - 1]);
    }

    for (int i = 0; i < 99; i++)
    {
        assert(h.extract() == remaining[i]);
    }
}

void test_binaryDictHeap_int_less()
{
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    dictHeap_int_less(h);
}

void test_binaryDictHeap_int_greater()
{
    BinaryDictHeap<int> h = BinaryDictHeap<int>(false);
    dictHeap_int_greater(h);
}

void test_binaryDictHeap_custom_less()
{
    BinaryDictHeap<MyStructDictHeap> h = BinaryDictHeap<MyStructDictHeap>(true);
    dictHeap_custom_less(h);
}

void test_binaryHeap_int_less_increaseKey()
{
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    dictHeap_int_less_increaseKey(h);
}

void test_binaryHeap_int_less_many()
{
    BinaryDictHeap<int> h = BinaryDictHeap<int>(true);
    dictHeap_int_less_many(h);
}

void test_fibonacciDictHeap_int_less()
{
    FibonacciDictHeap<int> h = FibonacciDictHeap<int>(true);
    dictHeap_int_less(h);
}

void test_fibonacciDictHeap_int_greater()
{
    FibonacciDictHeap<int> h = FibonacciDictHeap<int>(false);
    dictHeap_int_greater(h);
}

void test_fibonacciDictHeap_custom_less()
{
    FibonacciDictHeap<MyStructDictHeap> h = FibonacciDictHeap<MyStructDictHeap>(true);
    dictHeap_custom_less(h);
}

void test_fibonacciDictHeap_int_many()
{
    FibonacciDictHeap<int> h = FibonacciDictHeap<int>(true);
    dictHeap_int_less_many(h);
}