#define _CRT_SECURE_NO_WARNINGS

#include "Transactions.h"
#include <ctime>
#include <sstream>


Transaction::Transaction(int userID, int bookID, const std::string& type, IDGenerator& idGen)
    : UserID(userID), BookID(bookID), Type(type) {
    SetID(idGen);
    SetDate();
}

void Transaction::SetID(IDGenerator& idGen) {
    ID = idGen.GenerateID("Transaction");
}

void Transaction::SetID(int id) {
    if (id < 0) throw std::invalid_argument("Invalid transaction ID");
    ID = id;
}

void Transaction::SetUserID(int userID) {
    if (userID < 0) throw std::invalid_argument("Invalid user ID");
    UserID = userID;
}

void Transaction::SetBookID(int bookID) {
    if (bookID < 0) throw std::invalid_argument("Invalid book ID");
    BookID = bookID;
}

void Transaction::SetDate() {
    time_t now = time(0);
    Date = ctime(&now);
    Date.pop_back(); // Remove newline
}

void Transaction::SetType(const std::string& type) {
    if (type.empty() || type.length() > 50)
        throw std::invalid_argument("Type must be between 1 and 50 characters");
    Type = type;
}

void Transaction::SetDate(const std::string& date) {
    if (date.empty() || date.length() > 100)
        throw std::invalid_argument("Date must be between 1 and 100 characters");
    Date = date;
}

int Transaction::GetID() const {
    return ID;
}

int Transaction::GetUserID() const {
    return UserID;
}

int Transaction::GetBookID() const {
    return BookID;
}

const std::string& Transaction::GetType() const {
    return Type;
}

const std::string& Transaction::GetDate() const {
    return Date;
}