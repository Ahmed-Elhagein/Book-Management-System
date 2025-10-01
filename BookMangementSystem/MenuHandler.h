#pragma once


#include "BookManager.h"
#include "UserManager.h"
#include "TransactionManager.h"
#include <iostream>
#include <string>

class MenuHandler {
private:
    UserManager& userManager;
    BookManager& bookManager;
    TransactionManager& transManager;

    void ClearScreen() const;
    std::string GetInput(const std::string& prompt, bool allowEmpty = false) const;
    void PauseForUser() const;

    void HandleLogin();
    void HandleRegister();

    void AddBookScreen();
    void ViewAllBooksScreen();
    void SearchBookScreen();
    void UpdateBookScreen();
    void DeleteBookScreen();
    void SortBooksScreen();
    void FilterBooksScreen();

    void AddUserScreen();
    void ViewAllUsersScreen();
    void SearchUserScreen();
    void UpdateUserScreen();
    void DeleteUserScreen();

    void BorrowBookScreen();
    void ReturnBookScreen();
    void ViewTransactionsScreen();

public:
    MenuHandler(UserManager& um, BookManager& bm, TransactionManager& tm);
    void ShowWelcomeScreen();
    void ShowMainMenu();
    void HandleBookMenu();
    void HandleUserMenu();
    void HandleTransactionMenu();
    void HandleStatsMenu();
    void HandleChangePassword();
    void UnlockUserScreen();
    void LockUserScreen();
};