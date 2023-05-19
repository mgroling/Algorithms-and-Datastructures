#ifndef dictHeap
#define dictHeap

#include <functional>

#include "tuple"
#include "unordered_map"
#include "vector"

template <typename T>
class DictHeap {
   public:
    virtual void insert(T item, double priority) = 0;

    virtual T extract() = 0;

    virtual void changeKey(T item, double new_priority) = 0;

    virtual bool contains(T item) = 0;

    virtual int size() const = 0;

    virtual bool empty() const = 0;
};

template <typename T>
// Binary Heap that uses an array to save its elements
// also has a hash map to efficiently support the changeKey operation (includes decreaseKey and increaseKey)
// the supplied type must have the following methods implemented:
// operator= (assignment), operator== (equals), and must be hashable (std::hash must be implemented for it)
class BinaryDictHeap : public DictHeap<T> {
   public:
    BinaryDictHeap(bool isMinHeap) {
        if (isMinHeap) {
            comp = std::less<double>{};
        } else {
            comp = std::greater<double>{};
        }
    }

    void insert(T item, double priority) override {
        if (map.count(item)) {
            throw std::invalid_argument("Item is already present");
        }
        items.push_back(item);
        map[item] = std::tuple<int, double>{items.size() - 1, priority};
        bubbleUp(items.size() - 1);
    }

    T extract() override {
        // extracts the smallest element (if minHeap) or the greatest element (if maxHeap) (if tied, returns a random one)
        if (empty()) {
            throw std::out_of_range("Extract cannot be used on an empty heap");
        }
        T output = items[0];
        items[0] = items[items.size() - 1];
        map[items[0]] = std::tuple<int, double>{0, std::get<1>(map[items[0]])};
        items.pop_back();
        bubbleDown(0);
        map.erase(output);
        return output;
    }

    void changeKey(T item, double new_priority) override {
        // supports decrease and increase key
        if (!map.count(item)) {
            throw std::invalid_argument("Item is not present");
        }
        int index = std::get<0>(map[item]);
        double old_priority = std::get<1>(map[item]);
        map[item] = std::tuple<int, double>{index, new_priority};
        if (comp(new_priority, old_priority)) {
            // priority was decreased
            bubbleUp(index);
        } else {
            // priority was increased
            bubbleDown(index);
        }
    }

    bool contains(T item) {
        return map.count(item);
    }

    int size() const override {
        return items.size();
    }

    bool empty() const override {
        return !items.size();
    }

   private:
    std::vector<T> items;
    std::unordered_map<T, std::tuple<int, double>> map;
    std::function<bool(double, double)> comp;

    int getLeftChild(int index) const {
        return (index << 1) + 1;
    }

    int getComparatorChild(int index) const {
        // if the element does not have a child, this returns the passed index
        int leftChildIndex = getLeftChild(index);
        if (leftChildIndex >= items.size()) {
            return index;
        }
        // if the element only has a left child, then return its index
        if (leftChildIndex + 1 >= items.size()) {
            return leftChildIndex;
        }
        // create a const reference to the hash map, because otherwise we get a non-const reference when calling get, which violates
        // the constness of the function
        const std::unordered_map<T, std::tuple<int, double>> &constMap = map;
        // if the element has a left and a right child, then return the index of the one where comp(left, right) is true
        if (comp(std::get<1>(constMap.at(items[leftChildIndex])), std::get<1>(constMap.at(items[leftChildIndex + 1])))) {
            return leftChildIndex;
        }
        return leftChildIndex + 1;
    }

    int getParent(int index) const {
        // behaviour is only correct for nodes that have a parent (1..n), index = 0 will return -1
        return (index >> 1) - (index % 2 == 0);
    }

    void swap(const int &index1, const int &index2) {
        T temp = items[index1];
        items[index1] = items[index2];
        items[index2] = temp;
        map[items[index1]] = std::tuple<int, double>{index1, std::get<1>(map[items[index1]])};
        map[items[index2]] = std::tuple<int, double>{index2, std::get<1>(map[items[index2]])};
    }

    void bubbleUp(int index) {
        // the element of the given index is "bubbled" up towards the top of the heap (restoring the heap property on its path)
        int parentIndex = getParent(index);
        while (index != 0 && comp(std::get<1>(map[items[index]]), std::get<1>(map[items[parentIndex]]))) {
            swap(index, parentIndex);
            index = parentIndex;
            parentIndex = getParent(parentIndex);
        }
    }

    void bubbleDown(int index) {
        // the element of the given index is "bubbled" down towards the bottom of the heap (restoring the heap property on its path)
        int childIndex = getComparatorChild(index);
        while (index != childIndex && comp(std::get<1>(map[items[childIndex]]), std::get<1>(map[items[index]]))) {
            swap(index, childIndex);
            index = childIndex;
            childIndex = getComparatorChild(childIndex);
        }
    }
};

template <typename T>
class Node {
   public:
    T item;
    double priority;
    bool marked;
    int rank;
    Node *left;
    Node *right;
    Node *child

    Node(T item, double priority) {
        this->item = item;
        this->priority = priority;
        this->marked = false;
        this->rank = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->child = nullptr;
    }
};

template <typename T>
class FibonacciDictHeap : public DictHeap {
   public:
    FibonacciDictHeap(bool isMinHeap) {
        min = nullptr;
        if (isMinHeap) {
            comp = std::less<double>{};
        } else {
            comp = std::greater<double>{};
        }
    }

    void insert(T item, double priority) override {
        Node *ptr = new Node(item, priority);
        map[item] = ptr;
        if (min == nullptr) {
            min = ptr;
            ptr->right = ptr;
            ptr->left = ptr;
        } else {
            // append item to the right of the current minimum and update pointers
            Node *right = min->right;
            right->left = ptr;
            min->right = ptr;
            ptr->left = min;
            ptr->right = right;
            if (comp(priority, min->priority)) {
                min = ptr;
            }
        }
    }

    T extract() override;

    void changeKey(T item, double new_priority) override;

    bool contains(T item) override {
        return map.count(item);
    }

    int size() const override {
        return map.size();
    }

    bool empty() const override {
        return min == nullptr;
    }

   private:
    Node *min;
    std::unordered_map<T, Node *> map;
    std::function<bool(double, double)> comp;
};

#endif