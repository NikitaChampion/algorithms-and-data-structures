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

    void insert(int key);

    Node *find(int key) const;

    int splay(Node *node);

    int getHeight() const;

private:
    // your code
};
