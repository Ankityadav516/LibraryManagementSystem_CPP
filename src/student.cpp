#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() {}

Student::Student(string id, string name)
    : User(id, name, "Student") {}

void Student::display() const {
    cout << "Student ID: " << id << "\nName: " << name << "\nType: " << userType << "\n";
}
