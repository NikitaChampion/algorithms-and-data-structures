#include <iostream>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    Color color;

    Node();
    explicit Node(const T &x);
};

template <class ValueType>
class RBTree {
public:
    struct Iterator {
        Iterator();
        explicit Iterator(Node<ValueType> *node);

        const ValueType &operator*() const;
        const ValueType *operator->() const;

        Iterator &operator++();
        Iterator operator++(int);

        Iterator &operator--();
        Iterator operator--(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        // your code
    };

    RBTree();

    RBTree(const RBTree &other);

    RBTree<ValueType> &operator=(const RBTree &other);

    ~RBTree();

    void insert(const ValueType &value);

    void erase(const ValueType &value);

    size_t size() const;

    bool empty() const;

    Iterator lowerBound(const ValueType &value) const;

    Iterator find(const ValueType &value) const;

    Iterator begin() const;
 
    Iterator end() const;

    Node<ValueType> *root;

private:
    // your code
};
