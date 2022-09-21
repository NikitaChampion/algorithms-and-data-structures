#include <iterator>
#include <initializer_list>

class Vector {
public:
    struct Iterator {
        using IteratorCategory = std::random_access_iterator_tag;
        using DifferenceType = std::ptrdiff_t;

        explicit Iterator(int* ptr) : m_ptr_(ptr){};

        int& operator*() const;
        int* operator->();

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        Iterator operator+(const DifferenceType& movement);
        Iterator operator-(const DifferenceType& movement);

        Iterator& operator+=(const DifferenceType& movement);
        Iterator& operator-=(const DifferenceType& movement);

        friend bool operator==(const Iterator& a, const Iterator& b);
        friend bool operator!=(const Iterator& a, const Iterator& b);

    private:
        int* m_ptr_;
    };

    Vector();

    explicit Vector(size_t n_size);

    Vector(const int* vals, size_t size);

    Vector(const Vector& vec);

    Vector(std::initializer_list<int> vals);

    ~Vector();

    size_t getSize() const;

    size_t getCapacity() const;

    bool isEmpty() const;

    void resize(size_t n_size);

    void pushBack(int value);

    void popBack();

    void clear();

    void insert(size_t pos, int value);

    void erase(size_t pos);

    int at(size_t pos);

    int front();

    int back();

    Iterator begin();

    Iterator end();

    int& operator[](size_t pos) const;

    Vector& operator=(const Vector& other);

private:
    // your code
};
