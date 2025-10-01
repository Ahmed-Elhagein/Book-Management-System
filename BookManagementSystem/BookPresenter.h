#pragma once


#include "Book.h"
#include <vector>
#include <ostream>

class BookPresenter {

public:
    void PrintHeader(std::ostream& out = std::cout) const;
    void PrintFooter(std::ostream& out = std::cout) const;
    void DisplayBooks(const std::vector<Book>& books, std::ostream& out = std::cout) const;
    void DisplayBook(const Book& book, std::ostream& out = std::cout) const;
    void DisplayStats(const std::vector<Book>& books, std::ostream& out = std::cout) const;
};