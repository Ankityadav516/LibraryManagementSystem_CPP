#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    Student();
    Student(string id, string name);

    void display() const override;
};

#endif
