#pragma once

#include <string>


class IManager {

public:

    virtual ~IManager() = default;
    virtual void AddEntity() = 0;
    virtual void ViewAll() const = 0;
    virtual void Search(const std::string& query) const = 0;
};