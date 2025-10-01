#pragma once



#include "Transactions.h"
#include <vector>
#include <ostream>


class TransactionPresenter {

public:

    void PrintHeader(std::ostream& out = std::cout) const;
    void PrintFooter(std::ostream& out = std::cout) const;
    void DisplayTransactions(const std::vector<Transaction>& transactions, std::ostream& out = std::cout) const;
};
