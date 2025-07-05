#include "Transaction.h"
#include <iostream>
#include <sstream>

using namespace std;

Transaction::Transaction() {}

Transaction::Transaction(string uid, string bid, string idate, string rdate, string status)
    : userId(uid), bookId(bid), issueDate(idate), returnDate(rdate), status(status) {}

string Transaction::toCSV() const {
    return userId + "," + bookId + "," + issueDate + "," + returnDate + "," + status;
}

Transaction Transaction::fromCSV(const string& line) {
    stringstream ss(line);
    string uid, bid, idate, rdate, status;
    getline(ss, uid, ',');
    getline(ss, bid, ',');
    getline(ss, idate, ',');
    getline(ss, rdate, ',');
    getline(ss, status, ',');
    return Transaction(uid, bid, idate, rdate, status);
}

void Transaction::display() const {
    cout << "User ID: " << userId
         << "\nBook ID: " << bookId
         << "\nIssue Date: " << issueDate
         << "\nReturn Date: " << returnDate
         << "\nStatus: " << status << "\n";
}

string Transaction::getUserId() const { return userId; }
string Transaction::getBookId() const { return bookId; }
string Transaction::getStatus() const { return status; }
string Transaction::getIssueDate() const { return issueDate; }  // ✅ Needed in returnBook()
