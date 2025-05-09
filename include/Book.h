#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    std::string genre;
    int publicationYear;
    bool borrowed;

public:
    // Constructors
    Book();
    Book(int id, const std::string& title, const std::string& author, 
         const std::string& genre, int publicationYear);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getPublicationYear() const;
    bool isBorrowed() const;
    
    // Setters
    void setId(int id);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setGenre(const std::string& genre);
    void setPublicationYear(int year);
    
    // Book status
    void borrowBook();
    void returnBook();
    
    // String representation
    std::string toString() const;
};

#endif // BOOK_H