#pragma once

#include "User.h"
#include <vector>
#include <ostream>

class UserPresenter {

public:

    void PrintHeader(std::ostream& out = std::cout) const;
    void PrintFooter(std::ostream& out = std::cout) const;
    void DisplayUsers(const std::vector<User>& users, std::ostream& out = std::cout) const;
    void DisplayUser(const User& user, std::ostream& out = std::cout) const;
};
