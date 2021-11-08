#include <iostream>

class BTree {
public:
    explicit BTree(int);

    ~BTree();

    void insert(int);

    size_t size() const;

    int64_t sum() const;

private:
    // your code
};
