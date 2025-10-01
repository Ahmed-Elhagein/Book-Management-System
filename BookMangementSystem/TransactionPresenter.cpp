#include "TransactionPresenter.h"
#include <iomanip>

void TransactionPresenter::PrintHeader(std::ostream& out) const {
    out << "\n" << std::setw(85)
        << "\033[1;34m   _____________________________________________________________________________________________________\033[0m\n"
        << std::setw(10) << "| ID" << " | "
        << std::setw(15) << "User ID" << " | "
        << std::setw(15) << "Book ID" << " | "
        << std::setw(15) << "Type" << " | "
        << std::setw(30) << "Date" << " |\n"
        << std::setw(85) << "\033[1;34m   _____________________________________________________________________________________________________\033[0m\n\n";
}

void TransactionPresenter::PrintFooter(std::ostream& out) const {
    out << std::setw(85) << "\033[1;34m   _____________________________________________________________________________________________________\033[0m\n\n";
}

void TransactionPresenter::DisplayTransactions(const std::vector<Transaction>& transactions, std::ostream& out) const {
    if (transactions.empty()) {
        out << "\033[1;31mNo transactions found!\033[0m\n";
        return;
    }
    PrintHeader(out);
    for (const auto& trans : transactions) {
        out << std::setw(10) << trans.GetID() << " | "
            << std::setw(15) << trans.GetUserID() << " | "
            << std::setw(15) << trans.GetBookID() << " | "
            << std::setw(15) << trans.GetType() << " | "
            << std::setw(30) << trans.GetDate() << "\n";
    }
    PrintFooter(out);
}