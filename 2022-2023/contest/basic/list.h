class Node {
public:
    int data{};
    Node *next;
    Node *previous;

    Node();
};
 
class List {
public:
    List();
    List(int* values, size_t size);
    ~List();

    void pushBack(int value);
    void pushFront(int value);
    int pop();
    int pop(size_t position);
    void push(int value, size_t position);

    Node* head{};
    Node* tail{};
};
