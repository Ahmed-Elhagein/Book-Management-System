#pragma once


#include <string>
#include <unordered_map>
#include <fstream>
#include <stdexcept>


class IDGenerator {

private:

    std::string idFile;
    std::unordered_map<std::string, int> counters;

    void LoadCounters();

    void SaveCounters() const;

public:

    IDGenerator(const std::string& file);
    

    int GenerateID(const std::string& type);

    int GetLastID(const std::string& type) const;

};

