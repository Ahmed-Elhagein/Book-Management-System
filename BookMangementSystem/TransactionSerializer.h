
#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include "Transactions.h"
#include "IDGenerator.h"


class TransactionSerializer {

private:

    static void WriteString(std::ofstream& output, const std::string& str);
    static std::string ReadString(std::ifstream& input);

public:

    static void WriteToBinary(const Transaction& trans, std::ofstream& output);
    static Transaction ReadFromBinary(std::ifstream& input);
};


