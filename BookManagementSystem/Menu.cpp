// src/MenuHandler.cpp (Implementation file)

#include "Menu.h"
#include "Utilities.h"
#include <stdexcept>
#include <cstdlib>  // For system("cls")
#include <limits>   // For std::numeric_limits
#include <iostream>
#include <string>


MenuHandler::MenuHandler(UserManager& um, BookManager& bm, TransactionManager& tm)
    : userManager(um), bookManager(bm), transManager(tm) {
}

void MenuHandler::ClearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

std::string MenuHandler::GetInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin >> std::ws, value);  // Read full line after ignoring whitespace
    return value;
}

void MenuHandler::PauseForUser() const {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void MenuHandler::ShowWelcomeScreen() {
    ClearScreen();
    std::cout << "\n\n\t\tWelcome to Library Management System!\n\n";

    while (true) {
        std::cout << "\t\t1. Login\n"
            << "\t\t2. Register\n"
            << "\t\t3. Exit\n\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid input!\033[0m\n";
            PauseForUser();
            ClearScreen();
            std::cout << "\n\n\t\tWelcome to Library Management System!\n\n";
            continue;
        }

        try {
            std::string username, password, fullName, phone, email, address, role;
            int permissions;

            switch (choice) {
            case 1:
                HandleLogin();
                return;  // Proceed to main menu after successful login
            case 2:
                HandleRegister();
                break;
            case 3:
                std::cout << "\033[1;32mExiting the system. Goodbye!\033[0m\n";
                exit(0);
            default:
                std::cout << "\033[1;31mInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\tWelcome to Library Management System!\n\n";
    }
}

void MenuHandler::HandleLogin() {
    std::string username = GetInput("Username: ");
    std::string password = GetInput("Password: ");
    userManager.Login(username, password);
    std::cout << "\033[1;32mLogin successful! Welcome, " << username << "!\033[0m\n";
    PauseForUser();
    ShowMainMenu();
}

void MenuHandler::HandleRegister() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Register Screen ===========\n\n";
    std::string username = GetInput("Enter Username: ");
    std::string password = GetInput("Enter Password: ");
    std::string fullName = GetInput("Enter Full Name: ");
    std::string phone = GetInput("Enter Phone: ");
    std::string email = GetInput("Enter Email: ");
    std::string address = GetInput("Enter Address: ");
    std::string role = GetInput("Enter Role: ");
    int permissions;
    std::cout << "Enter Permissions: "; std::cin >> permissions;
    userManager.StoreUser(username, password, fullName, phone, email, address, role, permissions);
    std::cout << "\033[1;32mRegistration successful! You can now login.\033[0m\n";
}

void MenuHandler::ShowMainMenu() {
    while (true) {
        ClearScreen();
        std::cout << "\n\n\t\t=========== Main Menu ===========\n\n"
            << "\t\t1. Book Management\n"
            << "\t\t2. User Management\n"
            << "\t\t3. Transactions\n"
            << "\t\t4. Statistics\n"
            << "\t\t5. Logout/Exit\n\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid input! Please enter a number.\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            switch (choice) {
            case 1:
                HandleBookMenu();
                break;
            case 2:
                HandleUserMenu();
                break;
            case 3:
                HandleTransactionMenu();
                break;
            case 4:
                HandleStatsMenu();
                break;
            case 5:
                userManager.Logout();
                std::cout << "\033[1;32mExiting the system. Goodbye!\033[0m\n";
                return;
            default:
                std::cout << "\033[1;31mInvalid choice! Try again.\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
    }
}

void MenuHandler::HandleBookMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Book Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. Add Book\n"
            << "\t\t2. View All Books\n"
            << "\t\t3. Search Book\n"
            << "\t\t4. Update Book\n"
            << "\t\t5. Delete Book\n"
            << "\t\t6. Sort Books\n"
            << "\t\t7. Filter Books\n"
            << "\t\t8. Back to Main Menu\n\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid input!\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            switch (choice) {
            case 1:
                AddBookScreen();
                break;
            case 2:
                ViewAllBooksScreen();
                break;
            case 3:
                SearchBookScreen();
                break;
            case 4:
                UpdateBookScreen();
                break;
            case 5:
                DeleteBookScreen();
                break;
            case 6:
                SortBooksScreen();
                break;
            case 7:
                FilterBooksScreen();
                break;
            case 8:
                return;  // Back to main
            default:
                std::cout << "\033[1;31mInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\t=========== Book Screen ===========\n\n";
    }
}

void MenuHandler::AddBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Add Book Screen ===========\n\n";
    std::string title = GetInput("Enter Title: ");
    std::string author = GetInput("Enter Author: ");
    std::string category = GetInput("Enter Category: ");
    std::string description = GetInput("Enter Description: ");
    int year, quantity;
    double price;
    std::cout << "Enter Year: "; std::cin >> year;
    std::cout << "Enter Quantity: "; std::cin >> quantity;
    std::cout << "Enter Price: "; std::cin >> price;
    bookManager.StoreBook(title, author, category, description, year, quantity, price);
    std::cout << "\033[1;32mBook added successfully!\033[0m\n";
}

void MenuHandler::ViewAllBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== View All Books Screen ===========\n\n";
    bookManager.ViewAll();
}

void MenuHandler::SearchBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Search Book Screen ===========\n\n";
    std::string query = GetInput("Enter search query (title): ");
    bookManager.Search(query);
}

void MenuHandler::UpdateBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Update Book Screen ===========\n\n";
    int id;
    std::cout << "Enter Book ID: "; std::cin >> id;
    std::string title = GetInput("Enter new Title: ");
    std::string author = GetInput("Enter new Author: ");
    std::string category = GetInput("Enter new Category: ");
    std::string description = GetInput("Enter new Description: ");
    int year, quantity;
    double price;
    std::cout << "Enter new Year: "; std::cin >> year;
    std::cout << "Enter new Quantity: "; std::cin >> quantity;
    std::cout << "Enter new Price: "; std::cin >> price;
    bookManager.UpdateBook(id, title, author, category, description, year, quantity, price);
    std::cout << "\033[1;32mBook updated successfully!\033[0m\n";
}

void MenuHandler::DeleteBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Delete Book Screen ===========\n\n";
    int id;
    std::cout << "Enter Book ID: "; std::cin >> id;
    bookManager.DeleteBook(id);
    std::cout << "\033[1;32mBook deleted successfully!\033[0m\n";
}

void MenuHandler::SortBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Sort Books Screen ===========\n\n";
    std::string criterion = GetInput("Enter criterion (id/title/author/year/quantity/price/category): ");
    std::string order = GetInput("Enter order (ascending/descending): ");
    bookManager.SortBooks(criterion, order);
    std::cout << "\033[1;32mBooks sorted successfully!\033[0m\n";
}

void MenuHandler::FilterBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Filter Books Screen ===========\n\n";
    std::string title = GetInput("Enter Title (or empty): ");
    std::string author = GetInput("Enter Author (or empty): ");
    std::string category = GetInput("Enter Category (or empty): ");
    int year;
    std::cout << "Enter Year (or -1): "; std::cin >> year;
    bookManager.FilterBooks(title, author, category, year);
}

void MenuHandler::HandleUserMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== User Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. Add User\n"
            << "\t\t2. View All Users\n"
            << "\t\t3. Search User by ID\n"
            << "\t\t4. Update User\n"
            << "\t\t5. Delete User\n"
            << "\t\t6. Back to Main Menu\n\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid input!\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            switch (choice) {
            case 1:
                AddUserScreen();
                break;
            case 2:
                ViewAllUsersScreen();
                break;
            case 3:
                SearchUserScreen();
                break;
            case 4:
                UpdateUserScreen();
                break;
            case 5:
                DeleteUserScreen();
                break;
            case 6:
                return;  // Back to main
            default:
                std::cout << "\033[1;31mInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\t=========== User Screen ===========\n\n";
    }
}

void MenuHandler::AddUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Add User Screen ===========\n\n";
    std::string username = GetInput("Enter Username: ");
    std::string password = GetInput("Enter Password: ");
    std::string fullName = GetInput("Enter Full Name: ");
    std::string phone = GetInput("Enter Phone: ");
    std::string email = GetInput("Enter Email: ");
    std::string address = GetInput("Enter Address: ");
    std::string role = GetInput("Enter Role: ");
    int permissions;
    std::cout << "Enter Permissions: "; std::cin >> permissions;
    userManager.StoreUser(username, password, fullName, phone, email, address, role, permissions);
    std::cout << "\033[1;32mUser added successfully!\033[0m\n";
}

void MenuHandler::ViewAllUsersScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== View All Users Screen ===========\n\n";
    userManager.ViewAll();
}

void MenuHandler::SearchUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Search User Screen ===========\n\n";
    int id;
    std::cout << "Enter User ID: "; std::cin >> id;
    userManager.SearchUserByID(id);
}

void MenuHandler::UpdateUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Update User Screen ===========\n\n";
    int id;
    std::cout << "Enter User ID: "; std::cin >> id;
    std::string username = GetInput("Enter new Username: ");
    std::string password = GetInput("Enter new Password: ");
    std::string fullName = GetInput("Enter new Full Name: ");
    std::string phone = GetInput("Enter new Phone: ");
    std::string email = GetInput("Enter new Email: ");
    std::string address = GetInput("Enter new Address: ");
    std::string role = GetInput("Enter new Role: ");
    int permissions;
    std::cout << "Enter new Permissions: "; std::cin >> permissions;
    userManager.UpdateUser(id, username, password, fullName, phone, email, address, role, permissions);
    std::cout << "\033[1;32mUser updated successfully!\033[0m\n";
}

void MenuHandler::DeleteUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Delete User Screen ===========\n\n";
    int id;
    std::cout << "Enter User ID: "; std::cin >> id;
    userManager.DeleteUser(id);
    std::cout << "\033[1;32mUser deleted successfully!\033[0m\n";
}

void MenuHandler::HandleTransactionMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Transaction Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. Borrow Book\n"
            << "\t\t2. Return Book\n"
            << "\t\t3. View Transactions\n"
            << "\t\t4. Back to Main Menu\n\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid input!\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            switch (choice) {
            case 1:
                BorrowBookScreen();
                break;
            case 2:
                ReturnBookScreen();
                break;
            case 3:
                ViewTransactionsScreen();
                break;
            case 4:
                return;  // Back to main
            default:
                std::cout << "\033[1;31mInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\t=========== Transaction Screen ===========\n\n";
    }
}

void MenuHandler::BorrowBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Borrow Book Screen ===========\n\n";
    int userID, bookID;
    std::cout << "Enter User ID: "; std::cin >> userID;
    std::cout << "Enter Book ID: "; std::cin >> bookID;
    bookManager.BorrowBook(userID, bookID);
    std::cout << "\033[1;32mBook borrowed successfully!\033[0m\n";
}

void MenuHandler::ReturnBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Return Book Screen ===========\n\n";
    int userID, bookID;
    std::cout << "Enter User ID: "; std::cin >> userID;
    std::cout << "Enter Book ID: "; std::cin >> bookID;
    bookManager.ReturnBook(userID, bookID);
    std::cout << "\033[1;32mBook returned successfully!\033[0m\n";
}

void MenuHandler::ViewTransactionsScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== View Transactions Screen ===========\n\n";
    bookManager.ViewTransactions();
}

void MenuHandler::HandleStatsMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Stats Screen ===========\n\n";
    try {
        bookManager.ShowStats();
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}