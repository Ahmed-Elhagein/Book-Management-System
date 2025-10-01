#pragma once



#include "Book.h"
#include <fstream>
#include <string>

class Book;

class BookSerializer {

private:

    static void WriteString(std::ofstream& output, const std::string& str);
    static std::string ReadString(std::ifstream& input);

public:

    static void WriteToBinary(const Book& book, std::ofstream& output);
    static Book ReadFromBinary(std::ifstream& input);
};



