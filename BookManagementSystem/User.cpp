
#include "User.h"
#include <stdexcept>
#include <functional>
#include <sstream>
#include <iomanip>
#include <regex>
#include <random>
#include <chrono>
#include <iostream>

User::User() : ID(-1), Permissions(0),IsActive(true), LastLoginDate("") {}

User::User(const std::string& username, const std::string& password, const std::string& fullName,
    const std::string& phone, const std::string& email, const std::string& address,
    const std::string& role, int permissions, IDGenerator& idGen) {
    // Validate inputs first
    const std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (email.empty() || !std::regex_match(email, emailPattern)) {
        throw std::invalid_argument("Invalid email address");
    }

    const std::regex phonePattern(R"(\+201[0-5][0-9]{8}|01[0-5][0-9]{8})");
    if (phone.empty() || !std::regex_match(phone, phonePattern)) {
        throw std::invalid_argument("Invalid Egyptian phone number");
    }

    const std::regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
    if (password.empty() || !std::regex_match(password, passwordPattern)) {
        throw std::invalid_argument("Password must be at least 8 characters, include uppercase, lowercase, number, and special character");
    }

    // Initialize members
    ID = idGen.GenerateID("User");
    Username = username;
    std::string salt = GenerateSalt();
    Password = salt + ":" + HashPassword(password, salt);
    FullName = fullName.empty() ? "Unknown" : fullName;
    Phone = phone;
    Email = email;
    Address = address.empty() ? "Unknown" : address;
    Role = role.empty() ? "Unknown" : role;
    Permissions = permissions < 0 ? 0 : permissions;
    IsActive = true; 
    LastLoginDate = ""; 
}

std::optional<std::string> User::ValidateUserInput(const std::string& email, const std::string& phone, const std::string& password) {
    // Validate Email
    const std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (email.empty() || !std::regex_match(email, emailPattern)) {
        std::cout << "Debug: Invalid email: " << email << std::endl;
        return "Invalid email address";
    }

    // Validate Phone (Egyptian)
    const std::regex phonePattern(R"(\+201[0-5][0-9]{8}|01[0-5][0-9]{8})");
    if (phone.empty() || !std::regex_match(phone, phonePattern)) {
        std::cout << "Debug: Invalid phone: " << phone << std::endl;
        return "Invalid Egyptian phone number";
    }

    // Validate Password
    const std::regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
    if (password.empty() || !std::regex_match(password, passwordPattern)) {
        std::cout << "Debug: Invalid password: " << password << std::endl;
        return "Password must be at least 8 characters, include uppercase, lowercase, number, and special character";
    }

    return std::nullopt;
}

std::string User::GenerateSalt() {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    std::string salt(16, '\0');
    for (char& c : salt) {
        c = chars[dis(gen)];
    }
    return salt;
}

std::string User::HashPassword(const std::string& password, const std::string& salt) {
    std::string combined = salt + password;
    std::hash<std::string> hasher;
    size_t hash = hasher(combined);
    for (int i = 0; i < 1000; ++i) {
        hash = hasher(std::to_string(hash) + combined);
    }
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

bool User::VerifyPassword(const std::string& password, const std::string& stored) {
    size_t pos = stored.find(':');
    if (pos == std::string::npos) {
        return false;
    }
    std::string salt = stored.substr(0, pos);
    std::string storedHash = stored.substr(pos + 1);
    return HashPassword(password, salt) == storedHash;
}

// Getters
int User::GetID() const { return ID; }
const std::string& User::GetUsername() const { return Username; }
const std::string& User::GetPassword() const { return Password; }
const std::string& User::GetFullName() const { return FullName; }
const std::string& User::GetPhone() const { return Phone; }
const std::string& User::GetEmail() const { return Email; }
const std::string& User::GetAddress() const { return Address; }
const std::string& User::GetRole() const { return Role; }
int User::GetPermissions() const { return Permissions; }

// Setters
void User::SetID(int id) {
    if (id < 0) throw std::invalid_argument("Invalid user ID");
    ID = id;
}

void User::SetUsername(const std::string& username) {
    if (username.empty() || username.length() > 50)
        throw std::invalid_argument("Username must be between 1 and 50 characters");
    Username = username;
}

void User::SetPassword(const std::string& password) {
    const std::regex passwordPattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
    if (password.empty() || !std::regex_match(password, passwordPattern)) {
        std::cout << "Debug: Invalid password in SetPassword: " << password << std::endl;
        throw std::invalid_argument("Password must be at least 8 characters, include uppercase, lowercase, number, and special character");
    }
    std::string salt = GenerateSalt();
    Password = salt + ":" + HashPassword(password, salt);
}

void User::SetFullName(const std::string& fullName) {
    if (fullName.length() > 100)
        throw std::invalid_argument("Full name cannot exceed 100 characters");
    FullName = fullName.empty() ? "Unknown" : fullName;
}

void User::SetPhone(const std::string& phone) {
    const std::regex phonePattern(R"(\+201[0-5][0-9]{8}|01[0-5][0-9]{8})");
    if (phone.empty() || !std::regex_match(phone, phonePattern)) {
        throw std::invalid_argument("Invalid Egyptian phone number");
    }
    Phone = phone;
}

void User::SetEmail(const std::string& email) {
    const std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (email.empty() || !std::regex_match(email, emailPattern)) {
        throw std::invalid_argument("Invalid email address");
    }
    Email = email;
}

void User::SetAddress(const std::string& address) {
    if (address.length() > 200)
        throw std::invalid_argument("Address cannot exceed 200 characters");
    Address = address.empty() ? "Unknown" : address;
}

void User::SetRole(const std::string& role) {
    if (role.length() > 50)
        throw std::invalid_argument("Role cannot exceed 50 characters");
    Role = role.empty() ? "Unknown" : role;
}

void User::SetPermissions(int permissions) {
    if (permissions < 0)
        throw std::invalid_argument("Permissions cannot be negative");
    Permissions = permissions;
}

bool User::HasPermission(int permission) const {
    return (Permissions & permission) == permission;
}

void User::AddPermission(int permission) {
    Permissions |= permission;
}

void User::RemovePermission(int permission) {
    Permissions &= ~permission;
}

bool User::CheckPassword(const std::string& password) const {
    return VerifyPassword(password, Password);
}

void User::SetPasswordWithoutValidation(const std::string& password) {
    Password = password;
}

std::string User::GetLastLoginDate() const 
{ 
    return LastLoginDate; 
}

bool User::GetIsActive() const 
{ 
    return IsActive;
}

void User::SetLastLoginDate(const std::string& date) {
    LastLoginDate = date;
}

void User::SetActive(bool active) {
    IsActive = active;
}