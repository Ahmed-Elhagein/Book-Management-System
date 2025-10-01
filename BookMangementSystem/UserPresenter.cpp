
#include "UserPresenter.h"
#include <iomanip>

void UserPresenter::PrintHeader(std::ostream& out) const {
    out << "\n" << std::setw(120)
        << "\033[1;34m   ___________________________________________________________________________________________________________________________________________\033[0m\n"
        << std::setw(10) << "| ID" << " | "
        << std::setw(15) << "Username" << " | "
        << std::setw(20) << "Full Name" << " | "
        << std::setw(15) << "Phone" << " | "
        << std::setw(25) << "Email" << " | "
        << std::setw(20) << "Last Login" << " | "
        << std::setw(10) << "Active" << " |\n"
        << std::setw(120) << "\033[1;34m   ____________________________________________________________________________________________________________________________________________\033[0m\n\n";
}

void UserPresenter::PrintFooter(std::ostream& out) const {
    out << std::setw(120) << "\033[1;34m   ____________________________________________________________________________________________________________________________________________\033[0m\n\n";
}

void UserPresenter::DisplayUsers(const std::vector<User>& users, std::ostream& out) const {
    if (users.empty()) {
        out << "\033[1;31mNo users in system!\033[0m\n";
        return;
    }
    PrintHeader(out);
    for (const auto& user : users) {
        DisplayUser(user, out);
    }
    PrintFooter(out);
}

void UserPresenter::DisplayUser(const User& user, std::ostream& out) const {
    out << std::setw(10) << user.GetID() << " | "
        << std::setw(15) << user.GetUsername() << " | "
        << std::setw(20) << user.GetFullName() << " | "
        << std::setw(15) << user.GetPhone() << " | "
        << std::setw(25) << user.GetEmail() << " | "
        << std::setw(20) << (user.GetLastLoginDate().empty() ? "Never" : user.GetLastLoginDate()) << " | "
        << std::setw(10) << (user.GetIsActive() ? "Yes" : "No") << " |\n";
}