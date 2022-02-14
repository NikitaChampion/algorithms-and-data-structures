#pragma once

class Student;

class Ski {
    friend int compare(const Student &student, const Ski &ski);

    friend class ReadWriter;

private:
    int length_;

public:
    int id;
};

class Student {
    friend int compare(const Student &student, const Ski &ski);

    friend class ReadWriter;

private:
    int height_;

public:
    int id;
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
