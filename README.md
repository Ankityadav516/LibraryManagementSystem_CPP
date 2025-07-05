# 📘 Library Management System (C++ CLI Project)

This is a **console-based Library Management System** written in C++ as a self-project by **Ankit**, a student at **IIT Kanpur**. The system is designed to handle basic library operations like managing books, issuing/returning transactions, user role handling, and admin privileges.

---

## 🚀 Features

- 📖 **Book Management**
  - Add new books (admin only)
  - Display all books
  - Search books by title

- 🔁 **Transaction Management**
  - Issue and return books (with auto-generated dates)
  - Borrow limit: 2 books per user
  - Return due in 30 days with overdue warning

- 👤 **User Roles**
  - `Student`, `Faculty`, and `Admin` roles
  - Admin has special password-protected access
  - Each user can view their own transaction history

- 📁 **File Persistence**
  - Books and transactions are saved to CSV files
  - All data is loaded and saved automatically

---

## 🛠️ Technologies Used

- Language: **C++**
- File Handling: CSV via standard C++ file streams
- No external libraries used — fully standard C++

---

## 📂 Folder Structure
LibraryManagementSystem_CPP/
├── src/
│ ├── main.cpp
│ ├── Book.h / Book.cpp
│ ├── User.h / User.cpp
│ ├── Student.h / Student.cpp
│ ├── Faculty.h / Faculty.cpp
│ ├── Library.h / Library.cpp
│ ├── Transaction.h / Transaction.cpp
├── data/
│ ├── books.csv
│ ├── transactions.csv

---

## 🔓 Admin Access

To log in as admin:
- **User Type**: `Admin`
- **Password**: `Manager` (case-sensitive)

---

## 🧑‍💻 How to Run

### Compile:
```bash
g++ main.cpp Book.cpp User.cpp Student.cpp Faculty.cpp Transaction.cpp Library.cpp -o main

then run main 
Make sure the data/ directory contains books.csv and transactions.csv before you run the program.

