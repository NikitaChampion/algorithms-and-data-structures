template <class ValueType>
class Heap {
public:
    Heap();

    template <class Iterator>
    Heap(Iterator begin, Iterator end);

    Heap(std::initializer_list<ValueType>);

    Heap(const Heap &);
    Heap &operator=(const Heap &);

    Heap(Heap &&);
    Heap &operator=(Heap &&);

    ~Heap();

    size_t size() const;
    bool empty() const;

    void insert(const ValueType &);
    ValueType extract();
};
