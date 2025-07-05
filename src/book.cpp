#include "Book.h"
#include <iostream>
#include <sstream>
using namespace std;

Book::Book() {}

Book::Book(string id, string title, string author, int copies)
    : id(id), title(title), author(author), copies(copies) {}

string Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getCopies() const { return copies; }
void Book::setCopies(int c) { copies = c; }

string Book::toCSV() const {
    return id + "," + title + "," + author + "," + to_string(copies);
}

Book Book::fromCSV(const string &line) {
    stringstream ss(line);
    string id, title, author, copiesStr;
    getline(ss, id, ',');
    getline(ss, title, ',');
    getline(ss, author, ',');
    getline(ss, copiesStr, ',');
    int copies = stoi(copiesStr);
    return Book(id, title, author, copies);
}

void Book::display() const {
    cout << "ID: " << id << "\nTitle: " << title
         << "\nAuthor: " << author << "\nCopies: " << copies << "\n";
}
