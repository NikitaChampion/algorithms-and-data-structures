#include <iostream>

template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType key, ValueType value);
};

template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable();
    explicit HashTable(Func func);
    HashTable(size_t max_size, double coeff, Func func = std::hash<KeyType>());

    ~HashTable();

    void insert(KeyType key, ValueType data);
    void erase(KeyType key);

    ValueType *find(KeyType key);

    Node<KeyType, ValueType> &operator[](uint64_t index) const;
    Node<KeyType, ValueType> at(uint64_t index) const;

    size_t size() const;
    size_t capacity() const;

private:
    // your code
};
