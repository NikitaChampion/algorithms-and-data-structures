#include <iostream>
#include <string>

class BloomFilter {
public:
    BloomFilter(size_t hashes, size_t bits);

    ~BloomFilter();

    void add(const std::string &obj);

    bool verify(const std::string &obj);

    double getFPRate() const;

    size_t numberOfHashFunctions() const;
    size_t numberOfBits() const;

private:
    // your code
};
