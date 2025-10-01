
#include "UserSerializer.h"
#include <stdexcept>
#include <iostream>

void UserSerializer::WriteString(std::ofstream& output, const std::string& str) {
    if (!output.is_open()) {
        throw std::runtime_error("Output file is not open");
    }
    size_t size = str.size();
    output.write(reinterpret_cast<const char*>(&size), sizeof(size));
    output.write(str.c_str(), size);
}

std::string UserSerializer::ReadString(std::ifstream& input) {
    if (!input.is_open()) {
        throw std::runtime_error("Input file is not open");
    }
    size_t size;
    input.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (input.eof() || input.fail()) {
        std::cout << "Debug: Failed to read string size (EOF or fail)\n";
        return "";
    }
    std::string str(size, '\0');
    input.read(&str[0], size);
    if (input.fail()) {
        throw std::runtime_error("Error reading string data");
    }
    return str;
}

void UserSerializer::WriteToBinary(const User& user, std::ofstream& output) {
    /*std::cout << "Debug: Writing user: " << user.GetUsername() << " with ID: " << user.GetID() << std::endl;*/
    int id = user.GetID();
    output.write(reinterpret_cast<const char*>(&id), sizeof(id)); // Write ID
    WriteString(output, user.GetUsername());
    WriteString(output, user.GetPassword());
    /*std::cout << "Debug: Wrote password: " << user.GetPassword() << std::endl;*/
    WriteString(output, user.GetFullName());
    WriteString(output, user.GetPhone());
    WriteString(output, user.GetEmail());
    WriteString(output, user.GetAddress());
    WriteString(output, user.GetRole());
    int permissions = user.GetPermissions();
    output.write(reinterpret_cast<const char*>(&permissions), sizeof(permissions));

    WriteString(output, user.GetLastLoginDate()); // Write LastLoginDate
    bool isActive = user.GetIsActive();
    output.write(reinterpret_cast<const char*>(&isActive), sizeof(isActive)); // Write IsActive

    /*std::cout << "Debug: User written successfully\n";*/
}

User UserSerializer::ReadFromBinary(std::ifstream& input) {
    if (!input.is_open()) {
        throw std::runtime_error("Input file is not open");
    }
    if (input.peek() == EOF) {
        throw std::runtime_error("Empty file or end of file reached");
    }
    User user; // Default constructor sets ID = -1
    try {
        int id;
        input.read(reinterpret_cast<char*>(&id), sizeof(id)); // Read ID
        if (input.fail()) {
            throw std::runtime_error("Error reading user ID");
        }
        /*std::cout << "Debug: Read ID: " << id << std::endl;*/
        user.SetID(id); // Set ID explicitly

        std::string username = ReadString(input);
        /*std::cout << "Debug: Read username: " << username << std::endl;*/
        user.SetUsername(username);

        std::string password = ReadString(input);
       /* std::cout << "Debug: Read password: " << password << std::endl;*/
        user.SetPasswordWithoutValidation(password); // Skip validation for stored password

        std::string fullName = ReadString(input);
        /*std::cout << "Debug: Read fullName: " << fullName << std::endl;*/
        user.SetFullName(fullName);

        std::string phone = ReadString(input);
       /* std::cout << "Debug: Read phone: " << phone << std::endl;*/
        user.SetPhone(phone);

        std::string email = ReadString(input);
        /*std::cout << "Debug: Read email: " << email << std::endl;*/
        user.SetEmail(email);

        std::string address = ReadString(input);
        /*std::cout << "Debug: Read address: " << address << std::endl;*/
        user.SetAddress(address);

        std::string role = ReadString(input);
        /*std::cout << "Debug: Read role: " << role << std::endl;*/
        user.SetRole(role);

        int permissions;
        input.read(reinterpret_cast<char*>(&permissions), sizeof(permissions));
        if (input.fail()) {
            throw std::runtime_error("Error reading permissions");
        }
        /*std::cout << "Debug: Read permissions: " << permissions << std::endl;*/
        user.SetPermissions(permissions);


        std::string lastLoginDate = ReadString(input);
        /*std::cout << "Debug: Read lastLoginDate: " << lastLoginDate << std::endl;*/
        user.SetLastLoginDate(lastLoginDate);

        bool isActive;
        input.read(reinterpret_cast<char*>(&isActive), sizeof(isActive));
        if (input.fail()) {
            throw std::runtime_error("Error reading isActive");
        }
        /*std::cout << "Debug: Read isActive: " << isActive << std::endl;*/
        user.SetActive(isActive);



    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error reading user: " + std::string(e.what()));
    }
    return user;
}