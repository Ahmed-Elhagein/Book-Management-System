
#pragma once

#include <string>

#include<fstream>
#include <iomanip>
#include <iostream>
#include "IDGenerator.h"  
#include"BookSerializer.h"



class Book {

private:

    int ID;
    std::string Title;
    std::string Author;
    std::string Category;
    std::string Description;
    int Year;
    int Quantity;
    double Price;
    bool isAvailable;

    

public:
   
    //Constructors
    Book();
    Book(const std::string& title,
        const std::string& author,
        const std::string& category,
        const std::string& description,
        int year,
        int quantity,
        double price, IDGenerator& idGen);

   //Getters
    int GetID() const;
    const std::string& GetTitle() const;
    const std::string& GetAuthor() const;
    const std::string& GetCategory() const;
    const std::string& GetDescription() const;
    int GetYear() const;
    int GetQuantity() const;
    double GetPrice() const;
    bool GetIsAvailable() const;

    // Setters
    void SetStaticID(IDGenerator& idGen);
    void SetID(int ID);
    void SetTitle(const std::string& title);
    void SetAuthor(const std::string& author);
    void SetCategory(const std::string& category);
    void SetDescription(const std::string& description);
    void SetYear(int year);
    void SetQuantity(int quantity);
    void SetPrice(double price);
    void SetIsAvailable(bool available);

   
};


