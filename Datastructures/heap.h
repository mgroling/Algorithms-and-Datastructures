#ifndef heap
#define heap

#include <functional>

#include "vector"

template <typename T> class Heap
{
  public:
    virtual void insert(T item) = 0;

    virtual T extract() = 0;

    virtual int size() const = 0;

    virtual bool empty() const = 0;
};

template <typename T>
// Binary Heap that uses an array to save its elements
// the supplied type must have the following methods implemented:
// operator== (equals) and operator= (assignment)
class BinaryHeap : public Heap<T>
{
  public:
    // expects a comparator to compare two instances of T, giving "<" would result in a minHeap, and ">" would result in
    // a maxHeap
    BinaryHeap(std::function<bool(T, T)> comparator)
    {
        comp = comparator;
    }

    void insert(T item) override
    {
        items.push_back(item);
        bubbleUp(items.size() - 1);
    }

    T extract() override
    {
        // extracts the element e1 of the heap for which comp(e, e1) is false for all elements e of the heap
        if (empty())
        {
            throw std::out_of_range("Extract cannot be used on an empty heap");
        }
        T output = items[0];
        items[0] = items[items.size() - 1];
        items.pop_back();
        bubbleDown(0);
        return output;
    }

    int size() const override
    {
        return items.size();
    }

    bool empty() const override
    {
        return !items.size();
    }

  private:
    std::vector<T> items;
    std::function<bool(T, T)> comp;

    int getLeftChild(int index) const
    {
        return (index << 1) + 1;
    }

    int getComparatorChild(int index) const
    {
        // if the element does not have a child, this returns the passed index
        int leftChildIndex = getLeftChild(index);
        if (leftChildIndex >= items.size())
        {
            return index;
        }
        // if the element only has a left child, then return its index
        if (leftChildIndex + 1 >= items.size())
        {
            return leftChildIndex;
        }
        // if the element has a left and a right child, then return the index of the one where comp(left, right) is true
        if (comp(items[leftChildIndex], items[leftChildIndex + 1]))
        {
            return leftChildIndex;
        }
        return leftChildIndex + 1;
    }

    int getParent(int index) const
    {
        // behaviour is only correct for nodes that have a parent (1..n), index = 0 will return -1
        return (index >> 1) - (index % 2 == 0);
    }

    void swap(const int &index1, const int &index2)
    {
        T temp = items[index1];
        items[index1] = items[index2];
        items[index2] = temp;
    }

    void bubbleUp(int index)
    {
        // the element of the given index is "bubbled" up towards the top of the heap (restoring the heap property on
        // its path)
        int parentIndex = getParent(index);
        while (index != 0 && comp(items[index], items[parentIndex]))
        {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex = getParent(parentIndex);
        }
    }

    void bubbleDown(int index)
    {
        // the element of the given index is "bubbled" down towards the bottom of the heap (restoring the heap property
        // on its path)
        int childIndex = getComparatorChild(index);
        while (index != childIndex && comp(items[childIndex], items[index]))
        {
            swap(index, childIndex);
            index = childIndex;
            childIndex = getComparatorChild(childIndex);
        }
    }
};

#endif