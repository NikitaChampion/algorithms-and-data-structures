#include <iostream>

enum Color { RED, BLACK };

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K, V> *left;
    Node<K, V> *right;
    Node<K, v> *parent;
    Color color;

    Node();
    Node(const K &key, const V &value);
};

template <typename K, typename V>
class Map {
public:
    struct Iterator {
        Iterator();
        explicit Iterator(Node<K, V> *node);

        const std::pair<K, V> &operator*() const;
        const std::pair<K, V> *operator->() const;

        Iterator &operator++();
        Iterator operator++(int);

        Iterator &operator--();
        Iterator operator--(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        // your code
    };

    Map();
    Map(std::initializer_list<std::pair<K, V>> list);
    Map(const Map &other);

    Map<K, V> &operator=(const Map &other);

    ~Map();

    void insert(const K &key, const V &value);
    void erase(const K &key);

    size_t size() const;
    bool empty() const;

    Iterator lowerBound(const K &key) const;
    Iterator find(const K &key) const;

    Iterator begin() const;
    Iterator end() const;

    Node<K, V> *root;

private:
    // your code
};
