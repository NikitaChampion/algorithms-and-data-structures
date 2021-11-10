class BPlusTree {
public:
    explicit BPlusTree(int);

    ~BPlusTree();

    void insert(int);

    void printLeaves() const;

private:
    // your code
};
