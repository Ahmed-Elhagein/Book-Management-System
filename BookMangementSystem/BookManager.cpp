
#include "BookManager.h"
#include "Utilities.h"
#include <stdexcept>

BookManager::BookManager(const std::string& booksFile, const std::string& usersFile, const std::string& transFile,
    const std::string& idFile, UserManager& um, FileManager& fm, IDGenerator& ig)
    : filemanager(fm), userManager(um), idGen(ig), transManager(fm, um, ig) {
    Books = filemanager.LoadAllBooks();
}

int BookManager::FindBookByID(int ID) const {
    auto it = std::find_if(Books.begin(), Books.end(), [ID](const Book& book) { return ID == book.GetID(); });
    if (it == Books.end()) {
        throw std::runtime_error("\t\tBook not found");
    }
    return std::distance(Books.begin(), it);
}

bool BookManager::IsBookExist(const std::string& Title, const std::string& Author) const {
    auto lowerTitle = Utilities::ToLower(Title);
    auto lowerAuthor = Utilities::ToLower(Author);
    auto it = std::find_if(Books.begin(), Books.end(),
        [&](const Book& book) {
            return Utilities::ToLower(book.GetTitle()) == lowerTitle &&
                Utilities::ToLower(book.GetAuthor()) == lowerAuthor;
        });
    return it != Books.end();
}

void BookManager::AddEntity() {
    throw std::runtime_error("\t\tAddEntity not implemented for demo");
}

void BookManager::ViewAll() const {
    presenter.DisplayBooks(Books);
}

void BookManager::Search(const std::string& query) const {
    SearchBooks([query](const Book& book) {
        return Utilities::ToLower(book.GetTitle()).find(Utilities::ToLower(query)) != std::string::npos;
        });
}

template <typename Predicate>
void BookManager::SearchBooks(Predicate pred) const {
    std::vector<Book> results;
    for (const auto& book : Books) {
        if (pred(book)) {
            results.push_back(book);
        }
    }
    if (results.empty()) {
        throw std::runtime_error("\t\tNo books found for search criteria");
    }
   
    presenter.DisplayBooks(results);
    
}



void BookManager::SearchBook(const std::string& field, const std::string& value) const {
    std::string lowerField = Utilities::ToLower(field);
    std::string lowerValue = Utilities::ToLower(value);

    if (lowerField == "id") {
        int id = std::stoi(value);
        SearchBooks([id](const Book& book) {
            return book.GetID() == id;
            });
    }
    else if (lowerField == "title") {
        SearchBooks([lowerValue](const Book& book) {
            return Utilities::ToLower(book.GetTitle()).find(lowerValue) != std::string::npos;
            });
    }
    else if (lowerField == "author") {
        SearchBooks([lowerValue](const Book& book) {
            return Utilities::ToLower(book.GetAuthor()).find(lowerValue) != std::string::npos;
            });
    }
    else if (lowerField == "category") {
        SearchBooks([lowerValue](const Book& book) {
            return Utilities::ToLower(book.GetCategory()).find(lowerValue) != std::string::npos;
            });
    }
    else if (lowerField == "year") {
        int year = std::stoi(value);
        SearchBooks([year](const Book& book) {
            return book.GetYear() == year;
            });
    }
    else {
        throw std::invalid_argument("\t\tInvalid search field: " + field);
    }
}


void BookManager::StoreBook(const std::string& Title, const std::string& Author, const std::string& Category,
    const std::string& Description, int Year, int Quantity, double Price) {
    if (IsBookExist(Title, Author)) {
        throw std::invalid_argument("\t\tBook already exists");
    }
    if (Quantity < 0) {
        throw std::invalid_argument("\t\tQuantity cannot be negative");
    }
    Book book(Title, Author, Category, Description, Year, Quantity, Price, idGen);
    Books.push_back(book);
    filemanager.SaveBook(book);
}

void BookManager::DeleteBook(int ID) {
    int index = FindBookByID(ID);

    presenter.PrintHeader();
    presenter.DisplayBook(Books[index]);
    presenter.PrintFooter();


    char confirm = 'n';
    std::cout << "\n\t\tAre You Sure You Want to Delete This Book? (Y/N): ";
    std::cin >> confirm;
    if (std::tolower(confirm) == 'y') {
        Books.erase(Books.begin() + index);
        filemanager.SaveAllBooks(Books);
    }
    else {
        throw std::runtime_error("\t\tDeletion canceled by user");
    }
}

void BookManager::UpdateBook(int ID, const std::string& Title, const std::string& Author,
    const std::string& Category, const std::string& Description,
    int Year, int Quantity, double Price) {
    int index = FindBookByID(ID);
    presenter.DisplayBook(Books[index]);
    char confirm = 'n';
    std::cout << "\n\t\tAre You Sure You Want to Update This Book? (Y/N): ";
    std::cin >> confirm;
    if (std::tolower(confirm) == 'y') {
        Books[index].SetTitle(Title);
        Books[index].SetAuthor(Author);
        Books[index].SetCategory(Category);
        Books[index].SetDescription(Description);
        Books[index].SetYear(Year);
        if (Quantity < 0) throw std::invalid_argument("\t\tQuantity cannot be negative");
        Books[index].SetQuantity(Quantity);
        Books[index].SetPrice(Price);
        filemanager.SaveAllBooks(Books);
    }
    else {
        throw std::runtime_error("\t\tUpdate canceled by user");
    }
}

void BookManager::SortBooks(const std::string& Criterion, const std::string& Order) {
    std::string lowerOrder = Utilities::ToLower(Order);
    std::string lowerCriterion = Utilities::ToLower(Criterion);
    auto comparator = [&](const Book& b1, const Book& b2) -> bool {
        bool asc = lowerOrder == "ascending";
        if (lowerCriterion == "id") return asc ? b1.GetID() < b2.GetID() : b1.GetID() > b2.GetID();
        if (lowerCriterion == "title") return asc ? b1.GetTitle() < b2.GetTitle() : b1.GetTitle() > b2.GetTitle();
        if (lowerCriterion == "author") return asc ? b1.GetAuthor() < b2.GetAuthor() : b1.GetAuthor() > b2.GetAuthor();
        if (lowerCriterion == "year") return asc ? b1.GetYear() < b2.GetYear() : b1.GetYear() > b2.GetYear();
        if (lowerCriterion == "quantity") return asc ? b1.GetQuantity() < b2.GetQuantity() : b1.GetQuantity() > b2.GetQuantity();
        if (lowerCriterion == "price") return asc ? b1.GetPrice() < b2.GetPrice() : b1.GetPrice() > b2.GetPrice();
        if (lowerCriterion == "category") return asc ? b1.GetCategory() < b2.GetCategory() : b1.GetCategory() > b2.GetCategory();
        throw std::invalid_argument("\t\tInvalid sorting criterion");
        };
    std::sort(Books.begin(), Books.end(), comparator);
    filemanager.SaveAllBooks(Books);
}

void BookManager::FilterBooks(const std::string& Title, const std::string& Author, const std::string& Category, int Year) const {
    SearchBooks([Title, Author, Category, Year](const Book& book) {
        bool match = true;
        if (!Title.empty() && Utilities::ToLower(book.GetTitle()).find(Utilities::ToLower(Title)) == std::string::npos) match = false;
        if (!Author.empty() && Utilities::ToLower(book.GetAuthor()).find(Utilities::ToLower(Author)) == std::string::npos) match = false;
        if (!Category.empty() && Utilities::ToLower(book.GetCategory()).find(Utilities::ToLower(Category)) == std::string::npos) match = false;
        if (Year != -1 && book.GetYear() != Year) match = false;
        return match;
        });
}

void BookManager::ShowStats() const {
    presenter.DisplayStats(Books);
}

void BookManager::BorrowBook(int userID, int bookID) {
    transManager.BorrowBook(userID, bookID, Books);
}

void BookManager::ReturnBook(int userID, int bookID) {
    transManager.ReturnBook(userID, bookID, Books);
}

void BookManager::ViewTransactions() const {
    transManager.ViewAll();
}





