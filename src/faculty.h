#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

class Faculty : public User {
public:
    Faculty();
    Faculty(string id, string name);

    void display() const override;
};

#endif
