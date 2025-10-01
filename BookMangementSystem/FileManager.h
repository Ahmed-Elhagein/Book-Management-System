

#pragma once


#include <string>
#include <vector>
#include "Book.h"
#include "User.h"
#include "Transactions.h"
#include "BookSerializer.h"
#include "UserSerializer.h"
#include "TransactionSerializer.h"

class IStorage {

public:

    virtual void SaveBook(const Book& book) = 0;
    virtual std::vector<Book> LoadAllBooks() = 0;
    virtual void SaveAllBooks(const std::vector<Book>& books) = 0;
    virtual void SaveUser(const User& user) = 0;
    virtual std::vector<User> LoadAllUsers() = 0;
    virtual void SaveAllUsers(const std::vector<User>& users) = 0;
    virtual void SaveTransaction(const Transaction& transaction) = 0;
    virtual std::vector<Transaction> LoadAllTransactions() = 0;
    virtual void SaveAllTransactions(const std::vector<Transaction>& transactions) = 0;
    virtual ~IStorage() = default;

};

class FileManager : public IStorage {

private:
    std::string BooksFile;
    std::string UsersFile;
    std::string TransactionsFile;

public:

    FileManager(const std::string& booksFile, const std::string& usersFile, const std::string& transactionsFile);

    void SaveBook(const Book& book) override;
    std::vector<Book> LoadAllBooks() override;
    void SaveAllBooks(const std::vector<Book>& books) override;

    void SaveUser(const User& user) override;
    std::vector<User> LoadAllUsers() override;
    void SaveAllUsers(const std::vector<User>& users) override;

    void SaveTransaction(const Transaction& transaction) override;
    std::vector<Transaction> LoadAllTransactions() override;
    void SaveAllTransactions(const std::vector<Transaction>& transactions) override;

};
