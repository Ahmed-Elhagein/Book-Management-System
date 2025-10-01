#include "UserManager.h"
#include "Utilities.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>

UserManager::UserManager(FileManager& fm, IDGenerator& ig)
    : filemanager(fm), idGen(ig), currentUser(nullptr) {
    Users = filemanager.LoadAllUsers();
}

int UserManager::FindUserByID(int ID) const {
    auto it = std::find_if(Users.begin(), Users.end(), [ID](const User& user) { return user.GetID() == ID; });
    if (it == Users.end()) {
        throw std::runtime_error("\t\tUser not found");
    }
    return std::distance(Users.begin(), it);
}

bool UserManager::IsUserExist(const std::string& username) const {
    auto lowerUsername = Utilities::ToLower(username);
    auto it = std::find_if(Users.begin(), Users.end(),
        [lowerUsername](const User& user) {
            return Utilities::ToLower(user.GetUsername()) == lowerUsername;
        });
    return it != Users.end();
}

bool UserManager::IsUserExist(int userID) const {
    auto it = std::find_if(Users.begin(), Users.end(), [userID](const User& user) { return user.GetID() == userID; });
    return it != Users.end();
}

void UserManager::AddEntity() {
    throw std::runtime_error("\t\tAddEntity not implemented for demo");  // Call StoreUser with input if needed
}

void UserManager::ViewAll() const {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to view users");
    }
    presenter.DisplayUsers(Users);
}

void UserManager::Search(const std::string& query) const {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to search users");
    }
    SearchUsers([query](const User& user) {
        return Utilities::ToLower(user.GetUsername()).find(Utilities::ToLower(query)) != std::string::npos;
        });
}

template <typename Predicate>
void UserManager::SearchUsers(Predicate pred) const {
    std::vector<User> results;
    for (const auto& user : Users) {
        if (pred(user)) {
            results.push_back(user);
        }
    }
    if (results.empty()) {
        throw std::runtime_error("\t\tNo users found for search criteria");
    }
    presenter.DisplayUsers(results);
}

void UserManager::StoreUser(const std::string& username, const std::string& password, const std::string& fullName,
    const std::string& phone, const std::string& email, const std::string& address,
    const std::string& role, int permissions) {
    if (IsUserExist(username)) {
        throw std::invalid_argument("\t\tUser already exists");
    }
    User user(username, password, fullName, phone, email, address, role, permissions, idGen);
    Users.push_back(user);
    filemanager.SaveUser(user);
}

void UserManager::DeleteUser(int userID) {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to delete user");
    }
    int index = FindUserByID(userID);  // Throws if not found

    presenter.PrintHeader();
    presenter.DisplayUser(Users[index]);
    presenter.PrintFooter();

    char confirm = 'n';
    std::cout << "\n\t\tAre You Sure You Want to Delete This User? (Y/N): ";
    std::cin >> confirm;
    if (std::tolower(confirm) == 'y') {
        Users.erase(Users.begin() + index);
        filemanager.SaveAllUsers(Users);
    }
    else {
        throw std::runtime_error("\t\tDeletion canceled by user");
    }
}

void UserManager::UpdateUser(int userID, const std::string& username, const std::string& password, const std::string& fullName,
    const std::string& phone, const std::string& email, const std::string& address,
    const std::string& role, int permissions) {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to update user");
    }
    int index = FindUserByID(userID);  // Throws if not found

    presenter.PrintHeader();
    presenter.DisplayUser(Users[index]);
    presenter.PrintFooter();


    char confirm = 'n';
    std::cout << "\n\t\tAre You Sure You Want to Update This User? (Y/N): ";
    std::cin >> confirm;
    if (std::tolower(confirm) == 'y') {
        Users[index].SetUsername(username);
        Users[index].SetPassword(password);  // Assume hashing inside setter
        Users[index].SetFullName(fullName);
        Users[index].SetPhone(phone);
        Users[index].SetEmail(email);
        Users[index].SetAddress(address);
        Users[index].SetRole(role);
        Users[index].SetPermissions(permissions);
        filemanager.SaveAllUsers(Users);
    }
    else {
        throw std::runtime_error("\t\tUpdate canceled by user");
    }
}

void UserManager::SearchUserByID(int userID) const {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to search user");
    }
    int index = FindUserByID(userID);  // Throws if not found
    
    presenter.PrintHeader();
    presenter.DisplayUser(Users[index]);
    presenter.PrintFooter();

}

void UserManager::Login(const std::string& username, const std::string& password) {
    auto it = std::find_if(Users.begin(), Users.end(),
        [username, password](const User& user) {
            return user.GetUsername() == username && user.CheckPassword(password);
        });
    if (it != Users.end()) {
        currentUser = const_cast<User*>(&(*it));  // Cast to non-const
    }
    else {
        throw std::runtime_error("\t\tInvalid username or password");
    }

    

    std::string currentDate = Utilities::GetCurrentDate();
    /*std::cout << "Debug: Setting LastLoginDate to: " << currentDate << std::endl;*/
    currentUser = const_cast<User*>(&(*it));
    currentUser->SetLastLoginDate(currentDate);
    Users[std::distance(Users.begin(), it)] = *currentUser; // Update the vector
    filemanager.SaveAllUsers(Users);

}

void UserManager::Logout() {
    if (!currentUser) {
        throw std::runtime_error("\t\tNo user is currently logged in");
    }
    currentUser = nullptr;
}

User* UserManager::GetCurrentUser() const {
    return currentUser;
}


void UserManager::ChangePassword(const std::string& oldPass, const std::string& newPass) {
    if (!currentUser) {
        throw std::runtime_error("\t\tNo user is currently logged in");
    }
    if (!currentUser->CheckPassword(oldPass)) {
        throw std::runtime_error("\t\tOld password is incorrect");
    }
    currentUser->SetPassword(newPass);
    filemanager.SaveAllUsers(Users);
}

void UserManager::LockUser(int userID) {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to lock user");
    }
    int index = FindUserByID(userID);
    Users[index].SetActive(false);
    filemanager.SaveAllUsers(Users);
}

void UserManager::UnlockUser(int userID) {
    if (!currentUser || !currentUser->HasPermission(static_cast<int>(Permission::Admin))) {
        throw std::runtime_error("\t\tInsufficient permissions to unlock user");
    }
    int index = FindUserByID(userID);
    Users[index].SetActive(true);
    filemanager.SaveAllUsers(Users);
}