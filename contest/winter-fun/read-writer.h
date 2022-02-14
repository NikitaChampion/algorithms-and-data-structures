#include "student-ski.h"
#include <iostream>
#include <vector>

class ReadWriter {
public:
    ReadWriter() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    }

    int readInt() {
        int n;
        std::cin >> n;
        return n;
    }

    void readStudents(std::vector<Student> *arr) {
        char ch;
        for (size_t i = 0; i < arr->size(); ++i) {
            std::cin >> (*arr)[i].id >> (*arr)[i].height_ >> ch;
        }
    }

    void readSkis(std::vector<Ski> *arr) {
        char ch;
        for (size_t i = 0; i < arr->size(); ++i) {
            std::cin >> (*arr)[i].id >> (*arr)[i].length_ >> ch;
        }
    }

    void writeStudentsAndSkis(const std::vector<Student> &students, const std::vector<Ski> &skis) {
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << students[i].id << ' ' << skis[i].id << "; ";
        }
    }
};
