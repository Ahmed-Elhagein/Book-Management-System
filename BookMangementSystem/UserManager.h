
#pragma once

#include "IManager.h"
#include "FileManager.h"
#include "IDGenerator.h"
#include "User.h"
#include "UserPresenter.h"
#include <vector>
#include <string>
#include <functional>


enum class Permission {
    Admin = 1,
    Borrow = 2
    // Add more as needed
};

class UserManager : public IManager {

private:

    std::vector<User> Users;
    FileManager& filemanager;
    IDGenerator& idGen;
    User* currentUser;
    UserPresenter presenter;

    int FindUserByID(int ID) const;
   

public:

    UserManager(FileManager& fm, IDGenerator& ig);
    ~UserManager() = default;

    void AddEntity() override;
    void ViewAll() const override;
    void Search(const std::string& query) const override;

    template <typename Predicate>
    void SearchUsers(Predicate pred) const;

    void StoreUser(const std::string& username, const std::string& password, const std::string& fullName,
        const std::string& phone, const std::string& email, const std::string& address,
        const std::string& role, int permissions);
    void DeleteUser(int userID);
    void UpdateUser(int userID, const std::string& username, const std::string& password, const std::string& fullName,
        const std::string& phone, const std::string& email, const std::string& address,
        const std::string& role, int permissions);
    void SearchUserByID(int userID) const;
    void Login(const std::string& username, const std::string& password);
    void Logout();
    User* GetCurrentUser() const;
    bool IsUserExist(const std::string& username) const;
    bool IsUserExist(int userID) const;

    void ChangePassword(const std::string& oldPass, const std::string& newPass); 
    void LockUser(int userID); 
    void UnlockUser(int userID); 


};