#include "BookPresenter.h"
#include <iomanip>
#include <map>
#include <algorithm>

void BookPresenter::PrintHeader(std::ostream& out) const {

    out << "\n\n" << std::setw(108) << "   ____________________________________________________________________________________________________________________________________________\n"
        << std::setw(10) << "| ID" << " | "
        << std::setw(20) << "Title" << " | "
        << std::setw(20) << "Author" << " | "
        << std::setw(6) << "Year" << " | "
        << std::setw(8) << "Quantity" << " | "
        << std::setw(8) << "Price" << " | "
        << std::setw(15) << "Category" << " | "
        << std::setw(30) << "Description" << " |\n"
        << std::setw(108) << "   ____________________________________________________________________________________________________________________________________________\n\n";
}

void BookPresenter::PrintFooter(std::ostream& out) const {
    out << std::setw(108) << "   ____________________________________________________________________________________________________________________________________________\n\n";
}

void BookPresenter::DisplayBooks(const std::vector<Book>& books, std::ostream& out) const {
    if (books.empty()) {
        out << "\n\nNo Books Found !!\n\n";
        return;
    }
    PrintHeader(out);
    for (const auto& book : books) {
        DisplayBook(book, out);
    }
    PrintFooter(out);
}

void BookPresenter::DisplayBook(const Book& book, std::ostream& out) const {
    out << std::setw(10) << book.GetID() << " | "
        << std::setw(20) << book.GetTitle() << " | "
        << std::setw(20) << book.GetAuthor() << " | "
        << std::setw(6) << book.GetYear() << " | "
        << std::setw(8) << book.GetQuantity() << " | "
        << std::setw(8) << std::fixed << std::setprecision(2) << book.GetPrice() << " | "
        << std::setw(15) << book.GetCategory() << " | "
        << std::setw(30) << book.GetDescription() << " |\n";
}

void BookPresenter::DisplayStats(const std::vector<Book>& books, std::ostream& out) const {
    if (books.empty()) {
        out << "\n\nNo Books in System !!\n\n";
        return;
    }

    int totalBooks = books.size();
    double totalValue = 0.0;
    int totalQuantity = 0;
    std::map<std::string, int> categoryCount;
    std::map<std::string, int> authorBooks;
    Book oldest = books[0], newest = books[0], mostExpensive = books[0], cheapest = books[0];

    for (const auto& book : books) {
        totalQuantity += book.GetQuantity();
        totalValue += book.GetPrice() * book.GetQuantity();
        categoryCount[book.GetCategory()]++;
        authorBooks[book.GetAuthor()]++;
        if (book.GetYear() > newest.GetYear()) newest = book;
        if (book.GetYear() < oldest.GetYear()) oldest = book;
        if (book.GetPrice() > mostExpensive.GetPrice()) mostExpensive = book;
        if (book.GetPrice() < cheapest.GetPrice()) cheapest = book;
    }

    std::string mostCommonCategory = "None";
    int maxCount = 0;
    for (const auto& pair : categoryCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonCategory = pair.first;
        }
    }

    out << "\n\n\n\n\t\t=========== Library Statistics ===========\n\n"
        << "\t\t\tTotal Books: " << totalBooks << "\n"
        << "\t\t\tTotal Quantity: " << totalQuantity << "\n"
        << "\t\t\tTotal Value: $" << std::fixed << std::setprecision(2) << totalValue << "\n"
        << "\t\t\tMost Common Category: " << mostCommonCategory << " (" << maxCount << " books)\n"
        << "\t\t\tOldest Book: " << oldest.GetTitle() << "\t" << oldest.GetAuthor() << "\t" << oldest.GetYear() << "\n"
        << "\t\t\tNewest Book: " << newest.GetTitle() << "\t" << newest.GetAuthor() << "\t" << newest.GetYear() << "\n"
        << "\t\t\tMost Expensive Book: " << mostExpensive.GetTitle() << "\t" << mostExpensive.GetAuthor() << "\t$" << mostExpensive.GetPrice() << "\n"
        << "\t\t\tCheapest Book: " << cheapest.GetTitle() << "\t" << cheapest.GetAuthor() << "\t$" << cheapest.GetPrice() << "\n\n"
        << "\n\n\n\t\t===== Number of Books Per Author =====\n\n";

    for (const auto& pair : authorBooks) {
        out << "\t\t\t" << pair.first << "\t\t" << pair.second << "\n";
    }

    out << "\n\n\n\n\n\t\t========== Quantity Chart ==========\n\n";
    for (const auto& book : books) {
        out << "\t\t\t" << std::setw(20) << std::left << book.GetTitle() << " | "
            << " (" << book.GetQuantity() << ")\n";
    }
    out << "\n\n";
}