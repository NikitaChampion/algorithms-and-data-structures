#include <iostream>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType key, ValueType value);
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable();
    HashTable(Func f);
    HashTable(size_t size, double factor, Func f=std::hash<KeyType>());

    ~HashTable();

    void insert(KeyType key, ValueType value);
    ValueType *search(KeyType key);
    void remove(KeyType key);

    Node<KeyType, ValueType>& operator [](uint64_t hash);
    Node<KeyType, ValueType> at(uint64_t hash);
    
    size_t size() const;
    size_t capacity() const;
};
