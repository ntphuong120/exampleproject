#include "../include/Library.h"
#include <algorithm>
#include <cctype>

// Helper function for case-insensitive string comparison
bool containsCaseInsensitive(const std::string& str, const std::string& substr) {
    auto it = std::search(
        str.begin(), str.end(),
        substr.begin(), substr.end(),
        [](char ch1, char ch2) {
            return std::toupper(ch1) == std::toupper(ch2);
        }
    );
    return it != str.end();
}

Library::Library(const std::string& dataFile) : fileHandler(dataFile), nextBookId(1) {
    loadLibrary();
    
    // If books were loaded, find the next available ID
    if (!books.empty()) {
        int maxId = 0;
        for (const auto& book : books) {
            if (book.getId() > maxId) {
                maxId = book.getId();
            }
        }
        nextBookId = maxId + 1;
    }
}

bool Library::loadLibrary() {
    return fileHandler.loadBooks(books);
}

bool Library::saveLibrary() {
    return fileHandler.saveBooks(books);
}

int Library::findBookIndex(int id) const {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Library::addBook(const std::string& title, const std::string& author, 
                     const std::string& genre, int year) {
    if (title.empty() || author.empty()) {
        return false;  // Title and author are required
    }
    
    Book newBook(nextBookId++, title, author, genre, year);
    books.push_back(newBook);
    return saveLibrary();
}

bool Library::removeBook(int id) {
    int index = findBookIndex(id);
    if (index == -1) {
        return false;
    }
    
    books.erase(books.begin() + index);
    return saveLibrary();
}

bool Library::updateBook(int id, const std::string& title, const std::string& author,
                       const std::string& genre, int year) {
    Book* book = findBookById(id);
    if (!book) {
        return false;
    }
    
    if (!title.empty()) book->setTitle(title);
    if (!author.empty()) book->setAuthor(author);
    if (!genre.empty()) book->setGenre(genre);
    if (year > 0) book->setPublicationYear(year);
    
    return saveLibrary();
}

bool Library::borrowBook(int id) {
    Book* book = findBookById(id);
    if (!book || book->isBorrowed()) {
        return false;
    }
    
    book->borrowBook();
    return saveLibrary();
}

bool Library::returnBook(int id) {
    Book* book = findBookById(id);
    if (!book || !book->isBorrowed()) {
        return false;
    }
    
    book->returnBook();
    return saveLibrary();
}

Book* Library::findBookById(int id) {
    int index = findBookIndex(id);
    return (index != -1) ? &books[index] : nullptr;
}

std::vector<Book> Library::findBooksByTitle(const std::string& title) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (containsCaseInsensitive(book.getTitle(), title)) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::findBooksByAuthor(const std::string& author) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (containsCaseInsensitive(book.getAuthor(), author)) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::findBooksByGenre(const std::string& genre) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (containsCaseInsensitive(book.getGenre(), genre)) {
            result.push_back(book);
        }
    }
    return result;
}

int Library::getTotalBooks() const {
    return static_cast<int>(books.size());
}

int Library::getAvailableBooks() const {
    return static_cast<int>(std::count_if(books.begin(), books.end(), 
                                         [](const Book& b) { return !b.isBorrowed(); }));
}

int Library::getBorrowedBooks() const {
    return static_cast<int>(std::count_if(books.begin(), books.end(), 
                                         [](const Book& b) { return b.isBorrowed(); }));
}

const std::vector<Book>& Library::getAllBooks() const {
    return books;
}

std::vector<Book> Library::getAvailableBooksList() const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (!book.isBorrowed()) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> Library::getBorrowedBooksList() const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.isBorrowed()) {
            result.push_back(book);
        }
    }
    return result;
}

bool Library::createBackup(const std::string& backupFile) {
    // Save current state before creating backup
    if (!saveLibrary()) {
        return false;
    }
    return fileHandler.createBackup(backupFile);
}

bool Library::restoreFromBackup(const std::string& backupFile) {
    if (fileHandler.restoreFromBackup(backupFile)) {
        return loadLibrary();  // Reload books from the restored file
    }
    return false;
}