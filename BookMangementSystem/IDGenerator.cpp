#include "IDGenerator.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <stdexcept>



    void IDGenerator::LoadCounters() {

        std::ifstream input(idFile, std::ios::binary);
        if (!input.is_open()) return;
        while (input.peek() != EOF) {
            size_t typeSize;
            input.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize));
            if (typeSize > 100)
                throw std::runtime_error("Invalid ID type size in file: " + idFile);
            std::string type(typeSize, '\0');
            input.read(&type[0], typeSize);
            int counter;
            input.read(reinterpret_cast<char*>(&counter), sizeof(counter));
            counters[type] = counter;
        }
    }

    void IDGenerator::SaveCounters() const {
        std::ofstream output(idFile, std::ios::binary);
        if (!output.is_open())
            throw std::runtime_error("Failed to open ID file: " + idFile);
        for (const auto& pair : counters) {
            size_t typeSize = pair.first.size();
            output.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
            output.write(pair.first.c_str(), typeSize);
            output.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }
    }


    IDGenerator::IDGenerator(const std::string& file) : idFile(file) {
        LoadCounters();
    }

    int IDGenerator::GenerateID(const std::string& type) {
        int& counter = counters[type];
        counter = std::max(counter + 1, 1000); // Start from 1000
        SaveCounters();
        return counter;
    }

    int IDGenerator::GetLastID(const std::string& type) const {
        auto it = counters.find(type);
        return it != counters.end() ? it->second : 999;
    }



