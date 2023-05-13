#include <iostream>

#include "tuple"
#include "unordered_map"
#include "vector"

template <typename T>
class DictHeap {
   public:
    virtual void insert(T item) = 0;

    virtual T extract() = 0;

    virtual void changeKey(T item) = 0;

    virtual int size() const = 0;
};

template <typename T>
class BinaryDictHeap : public DictHeap<T> {
   public:
    BinaryDictHeap(std::function<bool(T, T)> comparator) {
        comp = comparator;
    }

    void insert(T item) override {
    }

    T extract() override {
    }

    void changeKey(T item) override {
    }

    int size() const override {
    }

   private:
    std::vector<T> items;
    std::unordered_map<T, std::tuple<int, int>> map;
    std::function<bool(T, T)> comp;
};