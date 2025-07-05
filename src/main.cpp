#include <iostream>
#include <limits>
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Faculty.h"
#include "Library.h"

using namespace std;

int main()
{
    Library lib;

    // Load books and transactions
    lib.loadFromFile("../data/books.csv");
    lib.loadTransactions("../data/transactions.csv");

    string currentUserId = "";
    string currentUserType = ""; // "Student", "Faculty", "Admin"

    while (true)
    {
        cout << "\n====== Library Management System ======\n";

        if (currentUserId == "")
        {
            cout << "You are not logged in.\n";
            cout << "1. Login\n";
            cout << "0. Exit\n";
        }
        else
        {
            cout << "Logged in as: " << currentUserId << " (" << currentUserType << ")\n";
            cout << "2. Search Book\n";
            cout << "3. Display All Books\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. View My Transactions\n";
            if (currentUserType == "Admin")
                cout << "7. Add New Book (Admin)\n";
            cout << "0. Logout\n";
        }

        cout << "Select option: ";
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (currentUserId == "")
        {
            switch (choice)
            {
            case 1:
            {
                cout << "Enter User ID: ";
                cin >> currentUserId;

                cout << "Enter User Type (Student/Faculty/Admin): ";
                cin >> currentUserType;

                // Normalize to uppercase
                for (char &c : currentUserType)
                    c = toupper(c);

                if (currentUserType == "ADMIN")
                {
                    string adminPass;
                    int attempts = 5;
                    bool success = false;

                    while (attempts--)
                    {
                        cout << "Enter Admin Password: ";
                        cin >> adminPass;

                        if (adminPass == "Manager")
                        {
                            cout << "Admin login successful.\n";
                            currentUserType = "Admin";
                            success = true;
                            break;
                        }
                        else
                        {
                            cout << "Incorrect password. ";
                            if (attempts > 0)
                                cout << attempts << " attempts left.\n";
                        }
                    }

                    if (!success)
                    {
                        cout << "Too many failed attempts. Exiting...\n";
                        return 0;
                    }
                }
                else if (currentUserType == "STUDENT" || currentUserType == "FACULTY")
                {
                    currentUserType[0] = toupper(currentUserType[0]);
                    for (size_t i = 1; i < currentUserType.size(); ++i)
                        currentUserType[i] = tolower(currentUserType[i]);

                    cout << "Logged in successfully.\n";
                }
                else
                {
                    cout << "Invalid user type. Logging out.\n";
                    currentUserId = "";
                    currentUserType = "";
                }

                break;
            }

            case 0:
                cout << "Exiting LMS. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid option. Please login first.\n";
            }
        }
        else
        {
            switch (choice)
            {
            case 0:
                cout << "Logged out successfully.\n";
                currentUserId = "";
                currentUserType = "";
                break;

            case 2:
            {
                cout << "Enter title or keyword to search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string keyword;
                getline(cin, keyword);
                lib.searchByTitle(keyword);
                break;
            }

            case 3:
                lib.displayAllBooks();
                break;

            case 4:
            {
                string bookId;
                cout << "Enter Book ID to issue: ";
                cin >> bookId;

                if (!lib.bookExists(bookId))
                {
                    cout << "Book ID not found in library.\n";
                    break;
                }

                lib.issueBook(currentUserId, bookId); 
                break;
            }

            case 5:
            {
                string bookId;
                cout << "Enter Book ID to return: ";
                cin >> bookId;
                lib.returnBook(currentUserId, bookId, ""); 
                break;
            }

            case 6:
                cout << "\n-- Your Issued Transactions --\n";
                lib.showUserTransactions(currentUserId);
                break;

            case 7:
            {
                if (currentUserType != "Admin")
                {
                    cout << "Access denied. Only admin can add books.\n";
                    break;
                }

                string id, title, author;
                int copies;
                cout << "Enter new Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter number of copies: ";
                cin >> copies;
                lib.addBook(Book(id, title, author, copies));
                cout << "Book added successfully!\n";
                break;
            }

            default:
                cout << "Invalid option. Try again.\n";
            }

            // Save all data after every action
            lib.saveToFile("../data/books.csv");
            lib.saveTransactions("../data/transactions.csv");
        }
    }

    return 0;
}
