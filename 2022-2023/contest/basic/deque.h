#include <iostream>

class Deque {
public:
    void pushBack(int value);
 
    void pushMiddle(int value);
 
    int popFront();

    int front() const;

    int back() const;

    size_t size() const;

private:
    // your code
};
