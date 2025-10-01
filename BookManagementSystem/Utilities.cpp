
#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"
#include <cctype>
#include <algorithm>
#include<sstream>
#include<iomanip>
#include<ctime>

namespace Utilities {

    std::string ToLower(std::string word) {

        for (char& c : word) {
            c = std::tolower(c);
        }

        return word;
    }

    std::string Utilities::GetCurrentDate() {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::stringstream ss;
        ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}