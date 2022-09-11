#pragma once

class Student;

class Ski {
    friend int compare(const Student &student, const Ski &ski);

    friend class ReadWriter;

public:
    int id;

private:
    int length_;
};

class Student {
    friend int compare(const Student &student, const Ski &ski);

    friend class ReadWriter;

public:
    int id;

private:
    int height_;
};

int compare(const Student &student, const Ski &ski) {
    if (ski.length_ < student.height_ + 5) {
        return -1;
    }
    if (ski.length_ > student.height_ + 5) {
        return 1;
    }
    return 0;
}
