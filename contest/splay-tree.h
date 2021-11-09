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

    Node *find(int) const;

    int splay(Node *);

    int getHeight() const;

private:
    // your code
};
