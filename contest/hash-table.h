#include <iostream>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType, ValueType);
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable();
    HashTable(Func);
    HashTable(size_t, double, Func = std::hash<KeyType>());

    ~HashTable();

    void insert(KeyType, ValueType);
    ValueType *search(KeyType);
    void erase(KeyType);

    Node<KeyType, ValueType> &operator[](uint64_t);
    Node<KeyType, ValueType> at(uint64_t);

    size_t size() const;
    size_t capacity() const;
};
