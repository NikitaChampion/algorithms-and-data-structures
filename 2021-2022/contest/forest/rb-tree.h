#include <iostream>

template <class ValueType>
class RBTree {
public:
    RBTree();

    RBTree(const RBTree &other);

    RBTree &operator=(const RBTree &other);

    ~RBTree();

    size_t size() const;

    bool empty() const;

    void insert(const ValueType &value);

    void erase(const ValueType &value);

    ValueType *lower_bound(const ValueType &value) const;  // NOLINT

    ValueType *find(const ValueType &value) const;

    ValueType *traversal() const;

private:
    // your code
};
