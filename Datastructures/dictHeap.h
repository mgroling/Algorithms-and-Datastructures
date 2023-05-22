#ifndef dictHeap
#define dictHeap

#include <cmath>
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
        if (contains(item)) {
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
    Node<T> *left;
    Node<T> *right;
    Node<T> *child;
    Node<T> *parent;

    Node(T item, double priority) {
        this->item = item;
        this->priority = priority;
        this->marked = false;
        this->rank = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->child = nullptr;
        this->parent = nullptr;
    }
};

template <typename T>
class FibonacciDictHeap : public DictHeap<T> {
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
        if (contains(item)) {
            throw std::invalid_argument("Item is already present");
        }
        Node<T> *ptr = new Node<T>(item, priority);
        map[item] = ptr;
        if (min == nullptr) {
            min = ptr;
            ptr->right = ptr;
            ptr->left = ptr;
        } else {
            addToRootList(ptr);
            if (comp(priority, min->priority)) {
                min = ptr;
            }
        }
    }

    T extract() override {
        // extracts the smallest element (if minHeap) or the greatest element (if maxHeap) (if tied, returns a random one)
        if (empty()) {
            throw std::out_of_range("Extract cannot be used on an empty heap");
        }
        T output = min->item;

        // add all children of min to the root list
        if (min->child != nullptr) {
            Node<T> *next_child = min->child->right;
            while (next_child != min->child) {
                next_child->parent = nullptr;
                next_child = next_child->right;
                addToRootList(next_child->left);
            }
            min->child->parent = nullptr;
            addToRootList(min->child);
        }

        // remove the old minimum
        min->right->left = min->left;
        min->left->right = min->right;
        map.erase(output);
        if (empty()) {
            min = nullptr;
            return output;
        }
        Node<T> *temp = min->right;
        delete min;
        min = temp;

        if (size()) {
            // find the new minimum
            Node<T> *cur = temp->right;
            while (cur != temp) {
                if (comp(cur->priority, min->priority)) {
                    min = cur;
                }
                cur = cur->right;
            }
            consolidate();
        } else {
            min = nullptr;
        }
        return output;
    }

    void changeKey(T item, double new_priority) override {
        // only supports decrease key
        if (!map.count(item)) {
            throw std::invalid_argument("Item is not present");
        }
        Node<T> *node = map[item];
        if (comp(node->priority, new_priority)) {
            throw std::invalid_argument("Priority must not be greater than before (in case of min heap, for max heap its vice versa)");
        }
        node->priority = new_priority;
        // if the heap property is violated cut the tree rooted at node, meld it into the root list, and unmark it
        // propagate to parent
        if (node->parent != nullptr && comp(new_priority, node->parent->priority)) {
            rebaseNode(node);
        }
        // check if item is new min
        if (comp(new_priority, min->priority)) {
            min = node;
        }
    }

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
    // the heap supports both min and max, but for simplicity we will refer to it as min
    Node<T> *min;
    std::unordered_map<T, Node<T> *> map;
    std::function<bool(double, double)> comp;

    void consolidate() {
        int size_v = int(std::log(size() + 1) / std::log(1.618)) + 1;
        std::vector<Node<T> *> rank_array(size_v, nullptr);

        Node<T> *cur_node = min;
        while (cur_node != min->left || rank_array[cur_node->rank] != nullptr) {
            if (rank_array[cur_node->rank] != nullptr && rank_array[cur_node->rank] != cur_node) {
                Node<T> *other_node = rank_array[cur_node->rank];
                rank_array[cur_node->rank] = nullptr;
                if (comp(cur_node->priority, other_node->priority)) {
                    merge(cur_node, other_node);
                } else {
                    merge(other_node, cur_node);
                    cur_node = other_node;
                }
            } else {
                rank_array[cur_node->rank] = cur_node;
                cur_node = cur_node->right;
            }
        }
    }

    void merge(Node<T> *node1, Node<T> *node2) {
        // it is assumed that comp(node1->priority, node2->priority) is true and they are both part of the root list
        // remove node 2 from the root list
        node2->left->right = node2->right;
        node2->right->left = node2->left;
        // add node2 as a child to node1
        if (node1->child == nullptr) {
            node1->child = node2;
            node2->right = node2;
            node2->left = node2;
        } else {
            // add node 2 to the right of the child
            node2->left = node1->child;
            node2->right = node1->child->right;
            node1->child->right->left = node2;
            node1->child->right = node2;
        }
        node2->parent = node1;
        node1->rank++;
    }

    void addToRootList(Node<T> *node) {
        // assumes that the root list has at least 1 element
        Node<T> *right = min->right;
        min->right->left = node;
        min->right = node;
        node->left = min;
        node->right = right;
    }

    void removeFromInnerTree(Node<T> *node) {
        // removes a node from the inner tree (removin the pointers from its siblings and parent to it)
        // remove the node from its siblings
        node->left->right = node->right;
        node->right->left = node->left;

        // remove the node from its parent
        // check if it is the direct child
        if (node->parent->child == node) {
            // check if it is the only child
            if (node->parent->child->right == node) {
                node->parent->child = nullptr;
            } else {
                node->parent->child = node->right;
            }
        }
    }

    void rebaseNode(Node<T> *node) {
        Node<T> *parent = node->parent;
        if (parent == nullptr) {
            return;
        }
        removeFromInnerTree(node);
        addToRootList(node);
        node->marked = false;
        node->parent = nullptr;

        // mark its parent, if its not marked yet, otherwise remove it as well
        if (parent->marked) {
            rebaseNode(node->parent);
        } else {
            parent->marked = true;
        }
    }
};

#endif