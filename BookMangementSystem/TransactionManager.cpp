#include "TransactionManager.h"
#include "Utilities.h"
#include <stdexcept>

TransactionManager::TransactionManager(FileManager& fm, UserManager& um, IDGenerator& ig)
    : filemanager(fm), userManager(um), idGen(ig) {
}

int TransactionManager::FindBookByID(int ID, const std::vector<Book>& books) {
    auto it = std::find_if(books.begin(), books.end(), [ID](const Book& book) { return ID == book.GetID(); });
    if (it == books.end()) {
        throw std::runtime_error("\t\tBook not found");
    }
    return std::distance(books.begin(), it);
}

void TransactionManager::AddEntity() {
    throw std::runtime_error("\t\tAdding manual transaction not supported");
}

void TransactionManager::ViewAll() const {
    if (!userManager.GetCurrentUser() || !userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to view transactions");
    }
    auto transactions = filemanager.LoadAllTransactions();
    presenter.DisplayTransactions(transactions);
}

void TransactionManager::Search(const std::string& query) const {
    auto transactions = filemanager.LoadAllTransactions();
    std::vector<Transaction> results;
    auto lowerQuery = Utilities::ToLower(query);
    for (const auto& trans : transactions) {
        if (Utilities::ToLower(trans.GetType()).find(lowerQuery) != std::string::npos) {
            results.push_back(trans);
        }
    }
    if (results.empty()) {
        throw std::runtime_error("\t\tNo transactions found for query");
    }
    presenter.DisplayTransactions(results);
}

void TransactionManager::BorrowBook(int userID, int bookID, std::vector<Book>& books) {
    if (!userManager.GetCurrentUser() /*|| !userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Borrow))*/) {
       
        throw std::runtime_error("\t\tYou must be logged in to borrow a book");
        /*throw std::runtime_error("\t\tInsufficient permissions to borrow a book");*/
    }
    int index = FindBookByID(bookID, books);
    if (!userManager.IsUserExist(userID)) {
        throw std::runtime_error("\t\tUser not found");
    }
    if (books[index].GetQuantity() <= 0) {
        throw std::out_of_range("\t\tBook is out of stock");
    }
    books[index].SetQuantity(books[index].GetQuantity() - 1);
    Transaction trans(userID, bookID, "Borrow", idGen);
    filemanager.SaveTransaction(trans);
    filemanager.SaveAllBooks(books);
}

void TransactionManager::ReturnBook(int userID, int bookID, std::vector<Book>& books) {
    if (!userManager.GetCurrentUser() /*|| !userManager.GetCurrentUser()->HasPermission(static_cast<int>(Permission::Borrow))*/) {
        
        throw std::runtime_error("\t\tYou must be logged in to return a book");
        /*throw std::runtime_error("\t\tInsufficient permissions to return a book");*/
    }
    int index = FindBookByID(bookID, books);
    if (!userManager.IsUserExist(userID)) {
        throw std::runtime_error("\t\tUser not found");
    }
    books[index].SetQuantity(books[index].GetQuantity() + 1);
    Transaction trans(userID, bookID, "Return", idGen);
    filemanager.SaveTransaction(trans);
    filemanager.SaveAllBooks(books);
}