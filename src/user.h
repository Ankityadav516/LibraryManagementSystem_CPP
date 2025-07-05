#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string id;
    string name;
    string userType; 

public:
    User();
    User(string id, string name, string userType);

    virtual void display() const;
    string toCSV() const;
    static User fromCSV(const string& line);

    string getId() const;
    string getUserType() const;
};

#endif
