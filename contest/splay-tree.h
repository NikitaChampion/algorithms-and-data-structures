struct Node {
public:
    int key;
    // your code

private:
    // your code
};

class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void insert(int);

    Node *find() const;

    int splay(Node *);

    int calcHeight() const;

private:
    // your code
};
