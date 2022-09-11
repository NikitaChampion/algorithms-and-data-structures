#include <iostream>

class Dequeue {
public:
    Dequeue();
 
    void pushBack(int value);
 
    void pushMiddle(int value);
 
    int popFront();
 
    int front() const;
 
    int back() const;
 
    size_t size() const;
 
    ~Dequeue();

private:
    // your code
};
