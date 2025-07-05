#include "Faculty.h"
#include <iostream>
using namespace std;

Faculty::Faculty() {}

Faculty::Faculty(string id, string name)
    : User(id, name, "Faculty") {}

void Faculty::display() const {
    cout << "Faculty ID: " << id << "\nName: " << name << "\nType: " << userType << "\n";
}
