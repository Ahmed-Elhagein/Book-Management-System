
#include "MenuHandler.h"
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

//std::string MenuHandler::GetInput(const std::string& prompt) const {
//    std::cout << prompt;
//    std::string value;
//    std::getline(std::cin>>std::ws , value);  // Read full line after ignoring whitespace
//    return value;
//}


std::string MenuHandler::GetInput(const std::string& prompt, bool allowEmpty ) const {
    std::cout << prompt;
    std::string value;

    if (allowEmpty) {
        std::cin.ignore();
        std::getline(std::cin, value); 
    }
    else {
        std::getline(std::cin >> std::ws, value); 
    }

    return value;
}






void MenuHandler::PauseForUser() const {
    std::cout << "\n\n\t\tPress Enter to continue...";
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
            << "\t\tEnter your choice: ";

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
            switch (choice) {
            case 1:
                HandleLogin();
                return;  // Proceed to main menu after successful login
            case 2:
                HandleRegister();
                break;
            case 3:
                std::cout << "\033[1;32m\t\tExiting the system. Goodbye!\033[0m\n";
                return;
            default:
                std::cout << "\033[1;31m\t\tInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\tWelcome to Library Management System!\n\n";
    }
}

void MenuHandler::HandleLogin() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Login Screen ===========\n\n";
    std::string username = GetInput("\t\tUsername: ");
    std::string password = GetInput("\t\tPassword: ");
    userManager.Login(username, password);
    std::cout << "\033[1;32m\t\tLogin successful! Welcome, " << username << "!\033[0m\n";
    PauseForUser();
    ShowMainMenu();
}

void MenuHandler::HandleRegister() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Register Screen ===========\n\n";
    std::string username = GetInput("\t\tEnter Username: ");
    std::string password = GetInput("\t\tEnter Password: ");
    std::string fullName = GetInput("\t\tEnter Full Name: ");
    std::string phone = GetInput("\t\tEnter Phone: ");
    std::string email = GetInput("\t\tEnter Email: ");
    std::string address = GetInput("\t\tEnter Address: ");
    std::string role = GetInput("\t\tEnter Role: ");
    int permissions;
    std::cout << "\t\tEnter Permissions (1 for Admin, 2 for User): "; std::cin >> permissions;

    const std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (email.empty() || !std::regex_match(email, emailPattern)) {
        std::cout << "\033[1;31m\t\tError: Invalid email address\033[0m\n";
        PauseForUser();
        return;
    }

    const std::regex phonePattern(R"(\+201[0-5][0-9]{8}|01[0-5][0-9]{8})");
    if (phone.empty() || !std::regex_match(phone, phonePattern)) {
        std::cout << "\033[1;31m\t\tError: Invalid Egyptian phone number\033[0m\n";
        PauseForUser();
        return;
    }

    const std::regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
    if (password.empty() || !std::regex_match(password, passwordPattern)) {
        std::cout << "\033[1;31m\t\tError: Password must be at least 8 characters, include uppercase, lowercase, number, and special character\033[0m\n";
        PauseForUser();
        return;
    }

    try {
        userManager.StoreUser(username, password, fullName, phone, email, address, role, permissions);
        std::cout << "\033[1;32m\t\tRegistration successful! You can now login.\033[0m\n";
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}

void MenuHandler::ShowMainMenu() {
    while (true) {
        ClearScreen();
        std::cout << "\n\n\t\t=========== Main Menu ===========\n\n"
            << "\t\t1. Book Management\n"
            << "\t\t2. Change Password\n";

        if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
            std::cout << "\t\t3. User Management\n";
        }

        std::cout << "\t\t4. Transactions\n";

        if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
            std::cout << "\t\t5. Statistics\n";
        }

        std::cout << "\t\t6. Logout/Exit\n\n"
            << "\t\tEnter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m\t\tInvalid input! Please enter a number.\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            switch (choice) {
            case 1:
                HandleBookMenu();
                break;

            case 2:

                HandleChangePassword();
                break;

            case 3:
                if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                    HandleUserMenu();
                }
                else {
                    std::cout << "\033[1;31m\t\tError: Insufficient permissions!\033[0m\n";
                }
                break;
            case 4:
                HandleTransactionMenu();
                break;
            case 5:
                if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                    HandleStatsMenu();
                }
                else {
                    std::cout << "\033[1;31m\t\tError: Insufficient permissions!\033[0m\n";
                }
                break;
            case 6:
                userManager.Logout();
                std::cout << "\033[1;32m\t\tExiting the system. Goodbye!\033[0m\n";
                return;
            default:
                std::cout << "\033[1;31m\t\tInvalid choice! Try again.\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
    }
}

void MenuHandler::HandleChangePassword() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Change Password Screen ===========\n\n";
    std::string oldPassword = GetInput("\t\tEnter Old Password: ");
    std::string newPassword = GetInput("\t\tEnter New Password: ");
    try {
        userManager.ChangePassword(oldPassword, newPassword);
        std::cout << "\033[1;32m\t\tPassword changed successfully!\033[0m\n";
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}

void MenuHandler::HandleBookMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Book Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. View All Books\n"
            << "\t\t2. Search Book\n"
            << "\t\t3. Filter Books\n";

        if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
            std::cout << "\t\t4. Add Book\n"
                << "\t\t5. Update Book\n"
                << "\t\t6. Delete Book\n"
                << "\t\t7. Sort Books\n";
        }

        std::cout << "\t\t" << (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin)) ? "8" : "4") << ". Back to Main Menu\n\n"
            << "\t\tEnter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m\t\tInvalid input!\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            if (choice == 1) {
                ViewAllBooksScreen();
            }
            else if (choice == 2) {
                SearchBookScreen();
            }
            else if (choice == 3) {
                FilterBooksScreen();
            }
            else if (choice == 4 && userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                AddBookScreen();
            }
            else if (choice == 5 && userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                UpdateBookScreen();
            }
            else if (choice == 6 && userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                DeleteBookScreen();
            }
            else if (choice == 7 && userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                SortBooksScreen();
            }
            else if (choice == (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin)) ? 8 : 4)) {
                return;  // Back to main
            }
            else {
                std::cout << "\033[1;31m\t\tInvalid choice or insufficient permissions!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\t=========== Book Screen ===========\n\n";
    }
}

void MenuHandler::AddBookScreen() {
    while (true) {
        ClearScreen();
        std::cout << "\n\n\t\t=========== Add Book Screen ===========\n\n";
        std::string title = GetInput("\t\tEnter Title: ");
        std::string author = GetInput("\t\tEnter Author: ");
        std::string category = GetInput("\t\tEnter Category: ");
        std::string description = GetInput("\t\tEnter Description: ");
        int year, quantity;
        double price;
        std::cout << "\t\tEnter Year: "; std::cin >> year;
        std::cout << "\t\tEnter Quantity: "; std::cin >> quantity;
        std::cout << "\t\tEnter Price: "; std::cin >> price;
        bookManager.StoreBook(title, author, category, description, year, quantity, price);
        std::cout << "\033[1;32m\t\tBook added successfully!\033[0m\n";

        char choice;
        std::cout << "\n\n\t\tDo you want to add another book? (y/n): ";
        std::cin >> choice;
        std::cin.ignore();

        if (tolower(choice) == 'n') {
            break;
        }
    }
}

void MenuHandler::ViewAllBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== View All Books Screen ===========\n\n";
    bookManager.ViewAll();
}

void MenuHandler::SearchBookScreen() {
    int choice;
    while (true) {
        ClearScreen();
        std::cout << "\n\t\t========== Book Search ==========\n"
            << "\t\t1. Search by ID\n"
            << "\t\t2. Search by Title\n"
            << "\t\t3. Search by Author\n"
            << "\t\t4. Search by Category\n"
            << "\t\t5. Search by Year\n"
            << "\t\t6. Back to Book Menu\n"
            << "\t\t=================================\n\n"
            << "\t\tEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        try {
            if (choice >= 1 && choice <= 5) {
                ClearScreen();
                std::string criterion;
                std::string prompt;
                switch (choice) {
                case 1: criterion = "id"; prompt = "Enter search query (ID): "; break;
                case 2: criterion = "title"; prompt = "Enter search query (Title): "; break;
                case 3: criterion = "author"; prompt = "Enter search query (Author): "; break;
                case 4: criterion = "category"; prompt = "Enter search query(Category) : "; break;
                case 5: criterion = "year"; prompt = "Enter search query (Year): "; break;
                }
                std::cout << "\n\t\t===== Search by " << criterion << " =====\n\n";
                std::string query = GetInput("\t\t" + prompt);
                bookManager.SearchBook(criterion, query);
                PauseForUser();
            }
            else if (choice == 6) {
                break;
            }
            else {
                std::cout << "\t\tInvalid choice. Try again.\n";
                PauseForUser();
            }
        }
        catch (const std::exception& ex) {
            std::cout << "\n\t\tError: " << ex.what() << "\n";
            PauseForUser();
        }
    }
}

void MenuHandler::UpdateBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Update Book Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter Book ID: "; std::cin >> id;
    std::cin.ignore();
    std::string title = GetInput("\t\tEnter new Title: ");
    std::string author = GetInput("\t\tEnter new Author: ");
    std::string category = GetInput("\t\tEnter new Category: ");
    std::string description = GetInput("\t\tEnter new Description: ");
    int year, quantity;
    double price;
    std::cout << "\t\tEnter new Year: "; std::cin >> year;
    std::cout << "\t\tEnter new Quantity: "; std::cin >> quantity;
    std::cout << "\t\tEnter new Price: "; std::cin >> price;
    std::cin.ignore();
    bookManager.UpdateBook(id, title, author, category, description, year, quantity, price);
    std::cout << "\033[1;32m\t\tBook updated successfully!\033[0m\n";
}

void MenuHandler::DeleteBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Delete Book Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter Book ID: "; std::cin >> id;
    std::cin.ignore();
    bookManager.DeleteBook(id);
    std::cout << "\033[1;32m\t\tBook deleted successfully!\033[0m\n";
}

void MenuHandler::SortBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Sort Books Screen ===========\n\n";
    std::string criterion = GetInput("\t\tEnter criterion (id/title/author/year/quantity/price/category): ");
    std::string order = GetInput("\t\tEnter order (ascending/descending): ");
    bookManager.SortBooks(criterion, order);
    std::cout << "\033[1;32m\t\tBooks sorted successfully!\033[0m\n";
}

void MenuHandler::FilterBooksScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Filter Books Screen ===========\n\n";
    std::string title = GetInput("\t\tEnter Title (or empty): ",true);
    std::string author = GetInput("\t\tEnter Author (or empty): ",true);
    std::string category = GetInput("\t\tEnter Category (or empty): ",true);
    int year;
    std::cout << "\t\tEnter Year (or -1): "; std::cin >> year;
    std::cin.ignore();
    bookManager.FilterBooks(title, author, category, year);
}

void MenuHandler::HandleUserMenu() {
    if (!userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
        std::cout << "\033[1;31m\t\tError: Insufficient permissions!\033[0m\n";
        PauseForUser();
        return;
    }
    ClearScreen();
    std::cout << "\n\n\t\t=========== User Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. Add User\n"
            << "\t\t2. View All Users\n"
            << "\t\t3. Search User by ID\n"
            << "\t\t4. Update User\n"
            << "\t\t5. Delete User\n"
            << "\t\t6. Lock User\n"
            << "\t\t7. Unlock User\n"
            << "\t\t8. Back to Main Menu\n\n"
            << "\t\tEnter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m\t\tInvalid input!\033[0m\n";
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

                LockUserScreen();
                break;

            case 7:

                UnlockUserScreen();
                break;


            case 8:
                return;  // Back to main
            default:
                std::cout << "\033[1;31m\t\tInvalid choice!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
        }
        PauseForUser();
        ClearScreen();
        std::cout << "\n\n\t\t=========== User Screen ===========\n\n";
    }
}


void MenuHandler::LockUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Lock User Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter User ID: "; std::cin >> id;
    std::cin.ignore();
    try {
        userManager.LockUser(id);
        std::cout << "\033[1;32m\t\tUser locked successfully!\033[0m\n";
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}

void MenuHandler::UnlockUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Unlock User Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter User ID: "; std::cin >> id;
    std::cin.ignore();
    try {
        userManager.UnlockUser(id);
        std::cout << "\033[1;32m\t\tUser unlocked successfully!\033[0m\n";
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}


void MenuHandler::AddUserScreen() {
    while (true) {
        ClearScreen();
        std::cout << "\n\n\t\t=========== Add User Screen ===========\n\n";
        std::string username = GetInput("\t\tEnter Username: ");
        std::string password = GetInput("\t\tEnter Password: ");
        std::string fullName = GetInput("\t\tEnter Full Name: ");
        std::string phone = GetInput("\t\tEnter Phone: ");
        std::string email = GetInput("\t\tEnter Email: ");
        std::string address = GetInput("\t\tEnter Address: ");
        std::string role = GetInput("\t\tEnter Role: ");
        int permissions;
        std::cout << "\t\tEnter Permissions (1 for Admin, 2 for User): "; std::cin >> permissions;
        std::cin.ignore();
        userManager.StoreUser(username, password, fullName, phone, email, address, role, permissions);
        std::cout << "\033[1;32m\t\tUser added successfully!\033[0m\n";

        char choice;
        std::cout << "\n\n\t\tDo you want to add another user? (y/n): ";
        std::cin >> choice;
        std::cin.ignore();

        if (tolower(choice) == 'n') {
            break;
        }
    }
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
    std::cout << "\t\tEnter User ID: "; std::cin >> id;
    std::cin.ignore();
    userManager.SearchUserByID(id);
}

void MenuHandler::UpdateUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Update User Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter User ID: "; std::cin >> id;
    std::cin.ignore();
    std::string username = GetInput("\t\tEnter new Username: ");
    std::string password = GetInput("\t\tEnter new Password: ");
    std::string fullName = GetInput("\t\tEnter new Full Name: ");
    std::string phone = GetInput("\t\tEnter new Phone: ");
    std::string email = GetInput("\t\tEnter new Email: ");
    std::string address = GetInput("\t\tEnter new Address: ");
    std::string role = GetInput("\t\tEnter new Role: ");
    int permissions;
    std::cout << "\t\tEnter new Permissions (1 for Admin, 2 for User): "; std::cin >> permissions;
    std::cin.ignore();
    userManager.UpdateUser(id, username, password, fullName, phone, email, address, role, permissions);
    std::cout << "\033[1;32m\t\tUser updated successfully!\033[0m\n";
}

void MenuHandler::DeleteUserScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Delete User Screen ===========\n\n";
    int id;
    std::cout << "\t\tEnter User ID: "; std::cin >> id;
    std::cin.ignore();
    userManager.DeleteUser(id);
    std::cout << "\033[1;32m\t\tUser deleted successfully!\033[0m\n";
}

void MenuHandler::HandleTransactionMenu() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Transaction Screen ===========\n\n";

    while (true) {
        std::cout << "\t\t1. Borrow Book\n"
            << "\t\t2. Return Book\n";

        if (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
            std::cout << "\t\t3. View Transactions\n"
                << "\t\t4. Back to Main Menu\n\n";
        }
        else {
            std::cout << "\t\t3. Back to Main Menu\n\n";
        }

        std::cout << "\t\tEnter your choice: ";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31m\t\tInvalid input!\033[0m\n";
            PauseForUser();
            continue;
        }

        try {
            if (choice == 1) {
                BorrowBookScreen();
            }
            else if (choice == 2) {
                ReturnBookScreen();
            }
            else if (choice == 3 && userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
                ViewTransactionsScreen();
            }
            else if (choice == (userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin)) ? 4 : 3)) {
                return;  // Back to main
            }
            else {
                std::cout << "\033[1;31m\t\tInvalid choice or insufficient permissions!\033[0m\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
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
    std::cout << "\t\tEnter User ID: "; std::cin >> userID;
    std::cout << "\t\tEnter Book ID: "; std::cin >> bookID;
    std::cin.ignore();
    bookManager.BorrowBook(userID, bookID);
    std::cout << "\033[1;32m\t\tBook borrowed successfully!\033[0m\n";
}

void MenuHandler::ReturnBookScreen() {
    ClearScreen();
    std::cout << "\n\n\t\t=========== Return Book Screen ===========\n\n";
    int userID, bookID;
    std::cout << "\t\tEnter User ID: "; std::cin >> userID;
    std::cout << "\t\tEnter Book ID: "; std::cin >> bookID;
    std::cin.ignore();
    bookManager.ReturnBook(userID, bookID);
    std::cout << "\033[1;32m\t\tBook returned successfully!\033[0m\n";
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
        std::cout << "\033[1;31m\t\tError: " << e.what() << "\033[0m\n";
    }
    PauseForUser();
}











