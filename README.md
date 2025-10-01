\# 📚 Book Management System



!\[C++](https://img.shields.io/badge/Language-C++17-blue?style=flat-square)

!\[Visual Studio](https://img.shields.io/badge/IDE-Visual\_Studio\_2022-purple?style=flat-square)

!\[Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=flat-square)

!\[License](https://img.shields.io/badge/License-MIT-green?style=flat-square)





---



\## 🔹 Introduction

A robust, object-oriented C++ application for managing a library's books, users, and transactions.  

Demonstrates \*\*OOP\*\* \& \*\*OOD\*\* principles with a modular, scalable, and maintainable design.  



---



\## 🔹 Key Features

\- \*\*Book Management\*\*: Add, remove, search, and update books.

\- \*\*User Management\*\*: Register users with role-based permissions (Admin, User, Guest).

\- \*\*Transaction Management\*\*: Borrow/return books with transaction logging and ID generation.

\- \*\*Security \& Validation\*\*: Password encryption, strength checking, and authentication system.

\- \*\*Data Persistence\*\*: Binary `.bin` files for storing books, users, and transactions.

\- \*\*Menu-Driven Interface\*\*: Console UI with input validation and easy navigation.



---





\## 🔹 System Design \& Architecture

\- \*\*Separation of Concerns (SoC)\*\*: Core logic is separated into managers (`BookManager`, `UserManager`, `TransactionManager`) for single-responsibility.

\- \*\*OOP Principles\*\*:

&nbsp; - \*\*Encapsulation\*\*: Private data members with public interfaces.

&nbsp; - \*\*Inheritance \& Polymorphism\*\*: Base interfaces for extensible manager classes.

&nbsp; - \*\*Composition over Inheritance\*\*: Presenters compose managers for display logic.

\- \*\*Modular Layers\*\*: 

&nbsp; - \*\*Model\*\*: Data classes (`Book`, `User`)

&nbsp; - \*\*Service\*\*: Managers for business logic

&nbsp; - \*\*Presenter\*\*: UI handling

&nbsp; - \*\*Persistence\*\*: Serializers for I/O

\- \*\*Error Handling \& Security\*\*: Custom exceptions, password encryption, input sanitization.

\- \*\*Design Patterns\*\*: Observer-like updates for transactions, Factory for ID generation, Strategy for serialization.





---



## 🔹 UML Class Diagram - Book Management System

```mermaid
classDiagram
%% Entities
class Book {
    +int ID
    +string Title
    +string Author
    +string Category
    +string Description
    +int Year
    +int Quantity
    +double Price
    +bool isAvailable
    +Book()
    +getters/setters
}

class User {
    +int ID
    +string Username
    +string Password
    +string FullName
    +string Phone
    +string Email
    +string Address
    +string Role
    +int Permissions
    +string LastLoginDate
    +bool IsActive
    +getters/setters
    +validatePassword()
    +permissionOperations()
}

class Transaction {
    +int ID
    +int UserID
    +int BookID
    +string Type
    +string Date
    +getters/setters
    +Transaction(IDGenerator)
}

%% Interfaces
class IManager {
    <<interface>>
    +AddEntity()
    +ViewAll()
    +Search(string)
}

class IStorage {
    <<interface>>
    +SaveBooks()
    +LoadBooks()
    +SaveUsers()
    +LoadUsers()
    +SaveTransactions()
    +LoadTransactions()
}

%% Managers
class BookManager {
    -vector~Book~ Books
    -FileManager& filemanager
    -UserManager& userManager
    -IDGenerator& idGen
    -BookPresenter presenter
    -TransactionManager transManager
    +CRUD()
    +Search()
    +Filter()
    +Sort()
    +BorrowReturn()
}

class UserManager {
    -vector~User~ Users
    -FileManager& filemanager
    -IDGenerator& idGen
    -User* currentUser
    -UserPresenter presenter
    +CRUD()
    +Login()
    +Logout()
    +LockUnlock()
    +ChangePassword()
}

class TransactionManager {
    -FileManager& filemanager
    -UserManager& userManager
    -IDGenerator& idGen
    -TransactionPresenter presenter
    +CRUD()
    +BorrowReturn()
}

%% Presenters
class BookPresenter {
    +DisplayBooks()
    +DisplayBook()
    +DisplayStats()
    +PrintHeader()
    +PrintFooter()
}

class UserPresenter {
    +DisplayUsers()
    +DisplayUser()
    +PrintHeader()
    +PrintFooter()
}

class TransactionPresenter {
    +DisplayTransactions()
    +PrintHeader()
    +PrintFooter()
}

%% Persistence
class FileManager {
    -string BooksFile
    -string UsersFile
    -string TransactionsFile
    +SaveBooks()
    +LoadBooks()
    +SaveUsers()
    +LoadUsers()
    +SaveTransactions()
    +LoadTransactions()
}

class BookSerializer {
    +WriteToBinary()
    +ReadFromBinary()
}

class UserSerializer {
    +WriteToBinary()
    +ReadFromBinary()
}

class TransactionSerializer {
    +WriteToBinary()
    +ReadFromBinary()
}

%% Utility
class IDGenerator {
    -string idFile
    -unordered_map~string, int~ counters
    +GenerateID(string type)
    +GetLastID(string type)
}

class MenuHandler {
    -UserManager& userManager
    -BookManager& bookManager
    -TransactionManager& transManager
    +ShowMenus()
    +HandleInputs()
}

%% Relationships
BookManager --|> IManager
UserManager --|> IManager
TransactionManager --|> IManager
FileManager --|> IStorage

BookManager ..> BookPresenter : uses
UserManager ..> UserPresenter : uses
TransactionManager ..> TransactionPresenter : uses

BookManager ..> FileManager : uses
UserManager ..> FileManager : uses
TransactionManager ..> FileManager : uses

BookManager ..> IDGenerator : uses
UserManager ..> IDGenerator : uses
TransactionManager ..> IDGenerator : uses

BookManager ..> UserManager : uses
BookManager ..> TransactionManager : uses

TransactionManager ..> Book : uses
TransactionManager ..> User : uses

FileManager ..> BookSerializer : uses
FileManager ..> UserSerializer : uses
FileManager ..> TransactionSerializer : uses

MenuHandler ..> UserManager : uses
MenuHandler ..> BookManager : uses
MenuHandler ..> TransactionManager : uses

```




---



\## 🔹 Technologies \& Tools

\- \*\*Language\*\*: C++17 (Standard Library)

\- \*\*IDE\*\*: Visual Studio 2022 (x64)

\- \*\*Build System\*\*: MSVC, CMake-ready structure

\- \*\*Libraries\*\*: Standard C++ (no external dependencies)



---





\## 🔹 How to Build and Run



1\. Clone the repository:

&nbsp;  git clone https://github.com/Ahmed-Elhagein/Book-Management-System


2\. Open in Visual Studio:


&nbsp;  - Navigate to the cloned folder: Book-Management-System.

&nbsp;  - Open BookManagementSystem.vcxproj (or BookManagementSystem.sln if available).

&nbsp;  - Set configuration to x64 Debug (or Release) in the top toolbar.





3\. Build:

&nbsp;  - Press Ctrl+Shift+B or Build > Build Solution

&nbsp;  - Executable appears in x64/Debug/



4\. Run:

&nbsp;  - Execute BookManagementSystem.exe

&nbsp;  - Follow the console menu to manage books, users, and transactions





---



\## 🔹 Sample Data



\- books.bin: Sample books

\- users.bin: Default admin (UserName: Ahmed, Password: Ahmed@1234) \& Default User (UserName: Sayed, Password:  Sayed@1234)

\- transactions.bin \& ids.bin: Empty for new sessions





---



\## 🔹 Future Enhancements



\- GUI integration (e.g., Qt)

\- SQLite database migration

\- REST API for web integration

\- Unit tests using Google Test



---



\## 🔹 About the Developer



Project developed by Ahmed Elhagein, 2025.

Showcases expertise in system design, OOP, and OOD, with clean, scalable code.







\*\*Connect with me:\*\*  

\[LinkedIn](https://www.linkedin.com/in/ahmed-elhagein-3b835731a) | \[GitHub](https://github.com/Ahmed-Elhagein)











