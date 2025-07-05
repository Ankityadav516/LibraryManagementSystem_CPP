#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string id;
    string title;
    string author;
    int copies;

public:
    Book(); 
    Book(string id, string title, string author, int copies);

    string getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getCopies() const;
    void setCopies(int c);

    string toCSV() const;
    static Book fromCSV(const string &line);
    void display() const;
};

#endif
