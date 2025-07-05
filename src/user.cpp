#include "User.h"
#include <iostream>
#include <sstream>
using namespace std;

User::User() {}

User::User(string id, string name, string userType)
    : id(id), name(name), userType(userType) {}

void User::display() const {
    cout << "User ID: " << id << "\nName: " << name << "\nType: " << userType << "\n";
}

string User::toCSV() const {
    return id + "," + name + "," + userType;
}

User User::fromCSV(const string& line) {
    stringstream ss(line);
    string id, name, type;
    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, type, ',');
    return User(id, name, type);
}

string User::getId() const { return id; }
string User::getUserType() const { return userType; }
