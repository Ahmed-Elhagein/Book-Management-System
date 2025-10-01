

#pragma once


#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include <random>
#include <chrono>
#include <optional> // Added for std::optional
#include "IDGenerator.h"

class User {
private:
    int ID;
    std::string Username;
    std::string Password; // Stored as {salt}:{hash}
    std::string FullName;
    std::string Phone;
    std::string Email;
    std::string Address;
    std::string Role;
    int Permissions;
    std::string LastLoginDate; 
    bool IsActive; 

    static std::optional<std::string> ValidateUserInput(const std::string& email, const std::string& phone, const std::string& password);
    static std::string GenerateSalt();
    static std::string HashPassword(const std::string& password, const std::string& salt);
    static bool VerifyPassword(const std::string& password, const std::string& stored);

public:
    User();
    User(const std::string& username, const std::string& password, const std::string& fullName,
        const std::string& phone, const std::string& email, const std::string& address,
        const std::string& role, int permissions, IDGenerator& idGen);

    // Getters
    int GetID() const;
    const std::string& GetUsername() const;
    const std::string& GetPassword() const; // Returns {salt}:{hash}
    const std::string& GetFullName() const;
    const std::string& GetPhone() const;
    const std::string& GetEmail() const;
    const std::string& GetAddress() const;
    const std::string& GetRole() const;
    int GetPermissions() const;
    std::string GetLastLoginDate() const; 
    bool GetIsActive() const; 


    // Setters
    void SetID(int id);
    void SetUsername(const std::string& username);
    void SetPassword(const std::string& password);
    void SetFullName(const std::string& fullName);
    void SetPhone(const std::string& phone);
    void SetEmail(const std::string& email);
    void SetAddress(const std::string& address);
    void SetRole(const std::string& role);
    void SetPermissions(int permissions);
    void SetLastLoginDate(const std::string& date); 
    void SetActive(bool active); 

    // Permission operations
    bool HasPermission(int permission) const;
    void AddPermission(int permission);
    void RemovePermission(int permission);

    // Password verification
    bool CheckPassword(const std::string& password) const;
    void SetPasswordWithoutValidation(const std::string& password);

    
};

