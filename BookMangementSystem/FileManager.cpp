
#include "FileManager.h"
#include <fstream>
#include <stdexcept>


FileManager::FileManager(const std::string& booksFile, const std::string& usersFile, const std::string& transactionsFile)
    : BooksFile(booksFile), UsersFile(usersFile), TransactionsFile(transactionsFile) {
}

void FileManager::SaveBook(const Book& book) {
    std::ofstream output(BooksFile, std::ios::binary | std::ios::app);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open books file: " + BooksFile);
    }
    BookSerializer::WriteToBinary(book, output);
}

std::vector<Book> FileManager::LoadAllBooks() {
    std::vector<Book> books;
    std::ifstream input(BooksFile, std::ios::binary);
    if (!input.is_open()) {
        /*throw std::runtime_error("Failed to open books file: " + BooksFile);*/
        std::cout << "Debug: Books file not found, returning empty list\n";
        return books;
    }
    while (input.peek() != EOF) {
        try {
            Book book = BookSerializer::ReadFromBinary(input);
            books.push_back(book);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error reading book: " + std::string(e.what()));
        }
    }
    return books;
}

void FileManager::SaveAllBooks(const std::vector<Book>& books) {
    std::ofstream output(BooksFile, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open books file: " + BooksFile);
    }
    for (const auto& book : books) {
        BookSerializer::WriteToBinary(book, output);
    }
}

void FileManager::SaveUser(const User& user) {
    std::ofstream output(UsersFile, std::ios::binary | std::ios::app);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open users file: " + UsersFile);
    }
    UserSerializer::WriteToBinary(user, output);
}

std::vector<User> FileManager::LoadAllUsers() {
    std::vector<User> users;
    std::ifstream input(UsersFile, std::ios::binary);
    if (!input.is_open()) {
        /*throw std::runtime_error("Failed to open users file: " + UsersFile);*/
        std::cout << "Debug: Users file not found, returning empty list\n";
        return users;
    }
    while (input.peek() != EOF) {
        try {
            User user = UserSerializer::ReadFromBinary(input);
            users.push_back(user);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error reading user: " + std::string(e.what()));
        }
    }
    return users;
}

void FileManager::SaveAllUsers(const std::vector<User>& users) {
    std::ofstream output(UsersFile, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open users file: " + UsersFile);
    }
    for (const auto& user : users) {
        UserSerializer::WriteToBinary(user, output);
    }
}

void FileManager::SaveTransaction(const Transaction& transaction) {
    std::ofstream output(TransactionsFile, std::ios::binary | std::ios::app);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open transactions file: " + TransactionsFile);
    }
    TransactionSerializer::WriteToBinary(transaction, output);
}

std::vector<Transaction> FileManager::LoadAllTransactions() {
    std::vector<Transaction> transactions;
    std::ifstream input(TransactionsFile, std::ios::binary);
    if (!input.is_open()) {
       /* throw std::runtime_error("Failed to open transactions file: " + TransactionsFile);*/
        std::cout << "Debug: Transactions file not found, returning empty list\n";
        return transactions;
    }
    while (input.peek() != EOF) {
        try {
            Transaction trans = TransactionSerializer::ReadFromBinary(input);
            transactions.push_back(trans);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error reading transaction: " + std::string(e.what()));
        }
    }
    return transactions;
}

void FileManager::SaveAllTransactions(const std::vector<Transaction>& transactions) {
    std::ofstream output(TransactionsFile, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open transactions file: " + TransactionsFile);
    }
    for (const auto& trans : transactions) {
        TransactionSerializer::WriteToBinary(trans, output);
    }
}



