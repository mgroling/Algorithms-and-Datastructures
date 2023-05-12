#include <iostream>

#include "vector"

template <typename T>
class Heap {
   public:
    virtual void insert(T item) = 0;

    virtual T extract() = 0;

    virtual int size() const = 0;

    virtual void print() const = 0;
};

template <typename T>
// Binary Heap that uses an array to save its elements
// first element of the array is the size of the heap
class BinaryHeap : public Heap<T> {
   public:
    // expects a comparator to compare two instances of T, giving "<" would result in a minHeap, and ">" would result in a maxHeap
    BinaryHeap(std::function<bool(T, T)> comparator) {
        comp = comparator;
        items.push_back(0);
    }

    void insert(T item) override {
        items.push_back(item);
        bubbleUp(++items[0]);
    }

    T extract() override {
        // extracts the element e1 of the heap for which comp(e1, e) is true for all elements e of the heap (except e1)
        if (size() == 0) {
            throw std::out_of_range("Extract cannot be used on an empty heap");
        }
        T output = items[1];
        items[1] = items[items[0]--];
        items.pop_back();
        bubbleDown(1);
        return output;
    }

    int size() const override {
        return items[0];
    }

    void print() const override {
        std::cout << "[";
        for (int i = 1; i <= items[0]; i++) {
            std::cout << items[i];
            if (i != items[0]) {
                std::cout << " ";
            }
        }
        std::cout << "]\n";
    }

   private:
    std::vector<T> items;
    std::function<bool(T, T)> comp;

    int getLeftChild(int index) const {
        return index << 1;
    }

    int getComparatorChild(int index) const {
        // if the element does not have a child, this returns the passed index
        int leftChildIndex = getLeftChild(index);
        if (leftChildIndex > items[0]) {
            return index;
        }
        // if the element only has a left child, then return its index
        if (leftChildIndex + 1 > items[0]) {
            return leftChildIndex;
        }
        // if the element has a left and a right child, then return the index of the one where comp(left, right) is true
        if (comp(items[leftChildIndex], items[leftChildIndex + 1])) {
            return leftChildIndex;
        }
        return leftChildIndex + 1;
    }

    int getParent(int index) const {
        return index >> 1;
    }

    void swap(const int &index1, const int &index2) {
        int temp = items[index1];
        items[index1] = items[index2];
        items[index2] = temp;
    }

    void bubbleUp(int index) {
        // the element of the given index is "bubbled" up towards the top of the heap
        int parentIndex = getParent(index);
        while (parentIndex != 0 && comp(items[index], items[parentIndex])) {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex = getParent(parentIndex);
        }
    }

    void bubbleDown(int index) {
        // the element of the given index is "bubbled" down towards the bottom of the heap
        int childIndex = getComparatorChild(index);
        while (comp(items[childIndex], items[index])) {
            swap(index, childIndex);
            index = childIndex;
            childIndex = getComparatorChild(childIndex);
        }
    }
};