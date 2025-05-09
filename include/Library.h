#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "../include/Book.h"
#include "../include/FileHandler.h"

class Library {
private:
    std::vector<Book> books;
    FileHandler fileHandler;
    int nextBookId;
    
    // Helper methods
    int findBookIndex(int id) const;
    
public:
    // Constructor
    Library(const std::string& dataFile = "data/Book.dat");
    
    // Library initialization
    bool loadLibrary();
    bool saveLibrary();
    
    // Book management
    bool addBook(const std::string& title, const std::string& author, 
                 const std::string& genre, int year);
    bool removeBook(int id);
    bool updateBook(int id, const std::string& title, const std::string& author,
                   const std::string& genre, int year);
    
    // Book borrowing system
    bool borrowBook(int id);
    bool returnBook(int id);
    
    // Book search functionality
    Book* findBookById(int id);
    std::vector<Book> findBooksByTitle(const std::string& title) const;
    std::vector<Book> findBooksByAuthor(const std::string& author) const;
    std::vector<Book> findBooksByGenre(const std::string& genre) const;
    
    // Library statistics
    int getTotalBooks() const;
    int getAvailableBooks() const;
    int getBorrowedBooks() const;
    
    // Book listing
    const std::vector<Book>& getAllBooks() const;
    std::vector<Book> getAvailableBooksList() const;
    std::vector<Book> getBorrowedBooksList() const;
    
    // Data management
    bool createBackup(const std::string& backupFile);
    bool restoreFromBackup(const std::string& backupFile);
};

#endif // LIBRARY_H