#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include "User.h"


//===========================================================
// Class: UserSerializer
// Description: Handles serialization and deserialization
// of User objects to and from binary files.
//===========================================================



class UserSerializer {

private:
    static void WriteString(std::ofstream& output, const std::string& str);
    static std::string ReadString(std::ifstream& input);

public:
    static void WriteToBinary(const User& user, std::ofstream& output);
    static User ReadFromBinary(std::ifstream& input);
};

