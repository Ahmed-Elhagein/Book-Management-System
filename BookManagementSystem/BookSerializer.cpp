
#include "BookSerializer.h"
#include "Book.h"
 


    void BookSerializer::WriteString(std::ofstream& output, const std::string& str) {

        size_t size = str.size();
        output.write(reinterpret_cast<const char*>(&size), sizeof(size));
        output.write(str.c_str(), size);
    }

   std::string BookSerializer::ReadString(std::ifstream& input) {

        size_t size;
        
        if (!input.read(reinterpret_cast<char*>(&size), sizeof(size)))
            throw std::runtime_error("Failed to read string size from file.");
       
        if (size > 1000) // Arbitrary limit to prevent memory issues
            throw std::runtime_error("String size exceeds maximum allowed length.");
        
        std::string temp(size, '\0');
        input.read(&temp[0], size);
        return temp;

   }



   void BookSerializer::WriteToBinary(const Book& book, std::ofstream& output)
   {
        int id = book.GetID();
        output.write(reinterpret_cast<const char*>(&id), sizeof(id));

        WriteString(output, book.GetTitle());
        WriteString(output, book.GetAuthor());
        WriteString(output, book.GetCategory());
        WriteString(output, book.GetDescription());


        int year = book.GetYear();
        output.write(reinterpret_cast<const char*>(&year), sizeof(year));

        int quantity = book.GetQuantity();
        output.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));

        double price = book.GetPrice();
        output.write(reinterpret_cast<const char*>(&price), sizeof(price));

        bool available = book.GetIsAvailable();
        output.write(reinterpret_cast<const char*>(&available), sizeof(available));
   }

    Book BookSerializer::ReadFromBinary(std::ifstream& input)
    {
        Book book;

        int id;
        if (!input.read(reinterpret_cast<char*>(&id), sizeof(id)))
            throw std::runtime_error("Failed to read ID from file.");
       
        if (id < 0)
            throw std::runtime_error("Invalid ID read from file.");
      
        
        book.SetID(id); 
        book.SetTitle(ReadString(input));
        book.SetAuthor(ReadString(input));
        book.SetCategory(ReadString(input));
        book.SetDescription(ReadString(input));

        int year;
        int quantity;
        double price;
        bool available;

        if (!input.read(reinterpret_cast<char*>(&year), sizeof(year)))
            throw std::runtime_error("Failed to read Year from file.");
        
        if (!input.read(reinterpret_cast<char*>(&quantity), sizeof(quantity)))
            throw std::runtime_error("Failed to read Quantity from file.");
        
        if (!input.read(reinterpret_cast<char*>(&price), sizeof(price)))
            throw std::runtime_error("Failed to read Price from file.");
        
        if (!input.read(reinterpret_cast<char*>(&available), sizeof(available)))
            throw std::runtime_error("Failed to read isAvailable from file.");
       
        
        book.SetYear(year);
        book.SetQuantity(quantity); 
        book.SetPrice(price);
        book.SetIsAvailable(available); 

        return book;
    }


