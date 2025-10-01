
#include"TransactionSerializer.h"

  

    void TransactionSerializer::WriteString(std::ofstream& output, const std::string& str) {
        size_t size = str.size();
        output.write(reinterpret_cast<const char*>(&size), sizeof(size));
        output.write(str.c_str(), size);
    }

   std::string TransactionSerializer::ReadString(std::ifstream& input) {
        size_t size;
        if (!input.read(reinterpret_cast<char*>(&size), sizeof(size)))
            throw std::runtime_error("Failed to read string size from file.");
        if (size > 1000)
            throw std::runtime_error("String size exceeds maximum allowed length.");
        std::string temp(size, '\0');
        input.read(&temp[0], size);
        return temp;
   }


    void TransactionSerializer::WriteToBinary(const Transaction& trans, std::ofstream& output) {
        int id = trans.GetID();
        int userID = trans.GetUserID();
        int bookID = trans.GetBookID();
        output.write(reinterpret_cast<const char*>(&id), sizeof(id));
        output.write(reinterpret_cast<const char*>(&userID), sizeof(userID));
        output.write(reinterpret_cast<const char*>(&bookID), sizeof(bookID));
        WriteString(output, trans.GetType());
        WriteString(output, trans.GetDate());
    }

    Transaction TransactionSerializer::ReadFromBinary(std::ifstream& input) {
        Transaction trans; // Default constructor
        try {
            int id, userID, bookID;
            if (!input.read(reinterpret_cast<char*>(&id), sizeof(id)))
                throw std::runtime_error("Failed to read Transaction ID from file.");
            if (!input.read(reinterpret_cast<char*>(&userID), sizeof(userID)))
                throw std::runtime_error("Failed to read User ID from file.");
            if (!input.read(reinterpret_cast<char*>(&bookID), sizeof(bookID)))
                throw std::runtime_error("Failed to read Book ID from file.");

            trans.SetID(id); // Use public setter
            trans.SetUserID(userID); // Use public setter
            trans.SetBookID(bookID); // Use public setter
            trans.SetType(ReadString(input));
            trans.SetDate(ReadString(input));

            return trans;
        }
        catch (const std::exception& e) {
            std::cerr << "\033[1;31mError reading transaction: " << e.what() << "\033[0m\n";
            return Transaction(); // Return default Transaction
        }
    }



