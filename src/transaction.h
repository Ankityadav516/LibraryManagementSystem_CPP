#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
private:
    string userId;
    string bookId;
    string issueDate;
    string returnDate;
    string status;

public:
    Transaction();
    Transaction(string uid, string bid, string idate, string rdate, string status);

    string toCSV() const;
    static Transaction fromCSV(const string& line);
    void display() const;

    string getUserId() const;
    string getBookId() const;
    string getStatus() const;
    string getIssueDate() const; 
};

#endif
