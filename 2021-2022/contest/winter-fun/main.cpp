#include "participant_solution.cpp"
#include "read-writer.h"

int main() {
    ReadWriter rw;

    int n = rw.readInt();

    std::vector<Student> students(n);
    std::vector<Ski> skis(n);

    rw.readStudents(&students);
    rw.readSkis(&skis);

    findPairs(&students, &skis);

    rw.writeStudentsAndSkis(students, skis);
    return 0;
}
