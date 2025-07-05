#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

bool Library::isValidDate(const string &date) const {
    struct tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

bool Library::bookExists(const string &bookId) const {
    for (const Book &b : books)
        if (b.getId() == bookId)
            return true;
    return false;
}

bool Library::alreadyBorrowed(const string &userId, const string &bookId) const {
    for (const Transaction &t : transactions)
        if (t.getUserId() == userId && t.getBookId() == bookId && t.getStatus() == "issued")
            return true;
    return false;
}

int Library::countIssuedBooks(const string &userId) const {
    int count = 0;
    for (const Transaction &t : transactions)
        if (t.getUserId() == userId && t.getStatus() == "issued")
            count++;
    return count;
}

void Library::addBook(const Book &book) {
    books.push_back(book);
}

void Library::displayAllBooks() const {
    cout << "\n-- Library Books --\n";
    for (const Book &b : books) {
        b.display();
        cout << "----------------\n";
    }
}

void Library::searchByTitle(const string &title) const {
    cout << "\n-- Search Results for \"" << title << "\" --\n";
    for (const Book &b : books) {
        if (b.toCSV().find(title) != string::npos) {
            b.display();
            cout << "----------------\n";
        }
    }
}

void Library::loadFromFile(const string &filename) {
    books.clear();
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        books.push_back(Book::fromCSV(line));
    }
    fin.close();
}

void Library::saveToFile(const string &filename) {
    ofstream fout(filename);
    for (const Book &b : books) {
        fout << b.toCSV() << endl;
    }
    fout.close();
}

void Library::issueBook(const string &userId, const string &bookId) {
    if (!bookExists(bookId)) {
        cout << "Error: Book ID not found in library.\n";
        return;
    }

    if (countIssuedBooks(userId) >= 2) {
        cout << "Error: Borrow limit reached (2 books). Return a book first.\n";
        return;
    }

    if (alreadyBorrowed(userId, bookId)) {
        cout << "Warning: You have already borrowed this book.\n";
        return;
    }

    for (Book &b : books) {
        if (b.getId() == bookId) {
            if (b.getCopies() > 0) {
                b.setCopies(b.getCopies() - 1);

                time_t now = time(0);
                struct tm *t = localtime(&now);
                char dateBuffer[11];
                strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", t);
                string issueDate = dateBuffer;

                transactions.emplace_back(userId, bookId, issueDate, "", "issued");

                time_t returnDeadline = now + 30 * 24 * 60 * 60;
                struct tm *deadline = localtime(&returnDeadline);
                char deadlineBuffer[11];
                strftime(deadlineBuffer, sizeof(deadlineBuffer), "%Y-%m-%d", deadline);

                cout << "Book issued successfully.\n";
                cout << "Please return by: " << deadlineBuffer << "\n";
                return;
            } else {
                cout << "Error: All copies of this book are already issued.\n";
                return;
            }
        }
    }
}

void Library::returnBook(const string &userId, const string &bookId, const string &) {
    if (!bookExists(bookId)) {
        cout << "Error: Book ID does not exist in library.\n";
        return;
    }

    for (Transaction &t : transactions) {
        if (t.getUserId() == userId && t.getBookId() == bookId && t.getStatus() == "issued") {
            string issueDate = t.getIssueDate();

            time_t now = time(0);
            struct tm *tstruct = localtime(&now);
            char returnBuffer[11];
            strftime(returnBuffer, sizeof(returnBuffer), "%Y-%m-%d", tstruct);
            string returnDate = returnBuffer;

            t = Transaction(userId, bookId, issueDate, returnDate, "returned");

            for (Book &b : books) {
                if (b.getId() == bookId) {
                    b.setCopies(b.getCopies() + 1);
                    break;
                }
            }

            struct tm issue_tm = {}, return_tm = {};
            istringstream iss(issueDate);
            istringstream rss(returnDate);
            iss >> get_time(&issue_tm, "%Y-%m-%d");
            rss >> get_time(&return_tm, "%Y-%m-%d");

            time_t issue_time = mktime(&issue_tm);
            time_t return_time = mktime(&return_tm);
            double diff_days = difftime(return_time, issue_time) / (60 * 60 * 24);

            cout << "Book returned successfully.\n";
            if (diff_days > 30) {
                cout << "Warning: Returned late by " << (int)(diff_days - 30) << " days.\n";
            }
            return;
        }
    }

    cout << "Error: You haven't borrowed this book or it's already returned.\n";
}

void Library::loadTransactions(const string &filename) {
    transactions.clear();
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        transactions.push_back(Transaction::fromCSV(line));
    }
    fin.close();
}

void Library::saveTransactions(const string &filename) {
    ofstream fout(filename);
    for (const Transaction &t : transactions) {
        fout << t.toCSV() << endl;
    }
    fout.close();
}

void Library::showAllTransactions() const {
    cout << "\n-- Transaction History --\n";
    for (const Transaction &t : transactions) {
        t.display();
        cout << "-------------------\n";
    }
}

void Library::showUserTransactions(const string &userId) const {
    bool found = false;
    for (const Transaction &t : transactions) {
        if (t.getUserId() == userId) {
            t.display();
            cout << "-------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No transactions found for this user.\n";
    }
}
