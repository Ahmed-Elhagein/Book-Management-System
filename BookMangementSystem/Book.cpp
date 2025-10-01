
#include "Book.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Default Constructor
Book::Book() : ID(-1), Title("Unknown"), Author("Unknown"), Category("Unknown"),
Description("None"), Year(0), Quantity(0), Price(0.0), isAvailable(false) {
}

// Parameterized Constructor

Book::Book(const std::string& title, const std::string& author, const std::string& category,
    const std::string& description, int year, int quantity, double price, IDGenerator& idGen) {
    SetStaticID(idGen);
    SetTitle(title);
    SetAuthor(author);
    SetCategory(category);
    SetDescription(description);
    SetYear(year);
    SetQuantity(quantity);
    SetPrice(price);
    SetIsAvailable(quantity > 0);
}


// Getters

int Book::GetID() const 
{ 
    return ID;
}

const std::string& Book::GetTitle() const
{ 
    return Title;
}

const std::string& Book::GetAuthor() const
{ 
    return Author;
}

const std::string& Book::GetCategory() const
{ 
    return Category; 
}

const std::string& Book::GetDescription() const
{ 
    return Description;
}

int Book::GetYear() const
{ 
    return Year;
}

int Book::GetQuantity() const 
{
    return Quantity;
}

double Book::GetPrice() const 
{ 
    return Price;
}

bool Book::GetIsAvailable() const
{ 
    return isAvailable; 
}

// Setters

void Book::SetStaticID(IDGenerator& idGen) {
    ID = idGen.GenerateID("Book");
}

void Book::SetID(int id) {

    if (id < 0)
        throw std::invalid_argument("Invalid book ID");
    ID = id;

}


void Book::SetTitle(const std::string& title)
{
    if (title.length() > 100)
        throw std::invalid_argument("Title cannot exceed 100 characters.");
    Title = title.empty() ? "Unknown" : title;
}

void Book::SetAuthor(const std::string& author) 
{
    if (author.length() > 100)
        throw std::invalid_argument("Author cannot exceed 100 characters.");
    Author = author.empty() ? "Unknown" : author;
}

void Book::SetCategory(const std::string& category) 
{
    if (category.length() > 50)
        throw std::invalid_argument("Category cannot exceed 50 characters.");
    Category = category.empty() ? "Unknown" : category;
}

void Book::SetDescription(const std::string& description) 
{
    if (description.length() > 500)
        throw std::invalid_argument("Description cannot exceed 500 characters.");
    Description = description.empty() ? "None" : description;
}

void Book::SetYear(int year) 
{
    if (year < 1500 || year > 2025)
        throw std::invalid_argument("Year must be between 1500 and 2025.");
    Year = year;
}

void Book::SetQuantity(int quantity)
{
    if (quantity < 0)
        throw std::invalid_argument("Quantity cannot be negative.");
    Quantity = quantity;
    isAvailable = Quantity > 0;
}

void Book::SetPrice(double price)
{
    if (price < 0.01 || price > 10000.0)
        throw std::invalid_argument("Price must be between 0.01 and 10000.0.");
    Price = price;
}

void Book::SetIsAvailable(bool available)
{
    if (available && Quantity <= 0)
        throw std::invalid_argument("Book cannot be available if quantity is zero.");
    isAvailable = available;
}

