#pragma once

#include "IManager.h"
#include "FileManager.h"
#include "UserManager.h"
#include "IDGenerator.h"
#include "TransactionPresenter.h"
#include <vector>
#include <string>




class TransactionManager : public IManager {

private:

    FileManager& filemanager;
    UserManager& userManager;
    IDGenerator& idGen;
    TransactionPresenter presenter;

    static int FindBookByID(int ID, const std::vector<Book>& books);

public:

    TransactionManager(FileManager& fm, UserManager& um, IDGenerator& ig);
    void AddEntity() override;
    void ViewAll() const override;
    void Search(const std::string& query) const override;
    void BorrowBook(int userID, int bookID, std::vector<Book>& books);
    void ReturnBook(int userID, int bookID, std::vector<Book>& books);
};
