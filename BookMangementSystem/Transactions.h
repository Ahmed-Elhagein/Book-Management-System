#pragma once 

#include <string>
#include<iostream>
#include <fstream>
#include <ctime>
#include "IDGenerator.h"

class Transaction {
private:
    int ID;
    int UserID;
    int BookID;
    std::string Type;
    std::string Date;

public:
    Transaction(int userID, int bookID, const std::string& type, IDGenerator& idGen);
    Transaction() : ID(-1), UserID(0), BookID(0), Type(""), Date("") {}

    // Getters
    int GetID() const;
    int GetUserID() const;
    int GetBookID() const;
    const std::string& GetType() const;
    const std::string& GetDate() const;

    // Setters
    void SetID(int id); // Added for deserialization
    void SetUserID(int userID); // Added for deserialization
    void SetBookID(int bookID); // Added for deserialization
    void SetType(const std::string& type);
    void SetDate(const std::string& date);
    void SetID(IDGenerator& idGen);
    void SetDate();
};


