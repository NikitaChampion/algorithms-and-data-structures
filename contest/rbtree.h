#include <iostream>

template <class ValueType>
class RBTree {
public:
    RBTree() {
        throw "Not implemented";
    }

    RBTree(const RBTree &other) {
        throw "Not implemented";
    }

    RBTree &operator=(const RBTree &other) {
        throw "Not implemented";
    }

    ~RBTree() {
        throw "Not implemented";
    }

    size_t size() const {
        throw "Not implemented";
    }

    bool empty() const {
        throw "Not implemented";
    }

    void insert(const ValueType &value) {
        throw "Not implemented";
    }

    void erase(const ValueType &value) {
        throw "Not implemented";
    }

    ValueType *lower_bound(const ValueType &value) const {  // NOLINT
        throw "Not implemented";
    }

    ValueType *find(const ValueType &value) const {
        throw "Not implemented";
    }

    ValueType *traversal() const {
        throw "Not implemented";
    }

private:
    // something
};

