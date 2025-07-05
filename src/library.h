#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Transaction.h"
#include <vector>
#include <string>

class Library
{
private:
    std::vector<Book> books;
    std::vector<Transaction> transactions;

    // Helper function to validate date format 
    bool isValidDate(const std::string &date) const;

public:
    // Book & borrow checks
    bool bookExists(const std::string &bookId) const;
    bool alreadyBorrowed(const std::string &userId, const std::string &bookId) const;
    int countIssuedBooks(const std::string &userId) const;

    // Book operations
    void addBook(const Book &book);
    void displayAllBooks() const;
    void searchByTitle(const std::string &title) const;
    void loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename);

    // Transaction operations
    void issueBook(const std::string &userId, const std::string &bookId);                 // auto issue date
    void returnBook(const std::string &userId, const std::string &bookId, const std::string &unused = ""); // auto return date
    void loadTransactions(const std::string &filename);
    void saveTransactions(const std::string &filename);
    void showAllTransactions() const;
    void showUserTransactions(const std::string &userId) const;
};

#endif
