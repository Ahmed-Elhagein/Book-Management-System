
#pragma once

#include "IManager.h"
#include "FileManager.h"
#include "UserManager.h"
#include "IDGenerator.h"
#include "BookPresenter.h"
#include "TransactionManager.h"
#include <vector>
#include <string>
#include <functional>

class BookManager : public IManager {

private:

    std::vector<Book> Books;
    FileManager& filemanager;
    UserManager& userManager;
    IDGenerator& idGen;
    BookPresenter presenter;
    TransactionManager transManager;

    int FindBookByID(int ID) const;
    bool IsBookExist(const std::string& Title, const std::string& Author) const;

public:

    BookManager(const std::string& booksFile, const std::string& usersFile, const std::string& transFile,
        const std::string& idFile, UserManager& um, FileManager& fm, IDGenerator& ig);
    void AddEntity() override;
    void ViewAll() const override;
    void Search(const std::string& query) const override;

    template <typename Predicate>
    void SearchBooks(Predicate pred) const;

    void SearchBook(const std::string& field, const std::string& value) const;




    void StoreBook(const std::string& Title, const std::string& Author, const std::string& Category,
        const std::string& Description, int Year, int Quantity, double Price);
    void DeleteBook(int ID);
    void UpdateBook(int ID, const std::string& Title, const std::string& Author,
        const std::string& Category, const std::string& Description,
        int Year, int Quantity, double Price);
    void SortBooks(const std::string& Criterion, const std::string& Order);
    void FilterBooks(const std::string& Title, const std::string& Author, const std::string& Category, int Year) const;
    void ShowStats() const;
    void BorrowBook(int userID, int bookID);
    void ReturnBook(int userID, int bookID);
    void ViewTransactions() const;
};
