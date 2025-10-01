#include "MenuHandler.h"
#include "FileManager.h"
#include "IDGenerator.h"
#include "UserManager.h"
#include "BookManager.h"
#include "TransactionManager.h"
#include <string>
#include <iostream>
#include <stdexcept>

int main() {

    try {

        FileManager fileManager("books.bin", "users.bin", "transactions.bin");
        IDGenerator idGen("ids.bin");
        UserManager userManager(fileManager, idGen);
        BookManager bookManager("books.bin", "users.bin", "transactions.bin", "ids.bin", userManager, fileManager, idGen);
        TransactionManager transManager(fileManager, userManager, idGen);
        MenuHandler menuHandler(userManager, bookManager, transManager);

        menuHandler.ShowWelcomeScreen();
    }
    catch (const std::exception& e) {
        std::cout << "\033[1;31m\t\tFatal Error: " << e.what() << "\033[0m\n";
    }

    return 0;
}