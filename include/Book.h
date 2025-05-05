// Định nghĩa lớp Book
#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>

enum class BookStatus {
    UNREAD,
    ONGOING,
    DONE,
    AVAILABLE,
    UNAVAILABLE
};

class Book {
private:
    int id;
    std::string title;
    std::string author;
    std::vector<std::string> genre;
    int numberPage;
    int publicationYear;
    BookStatus status;
public:
    Book(int id, const std::string& title, const std::string& author, const std::vector<std::string>& genre,
        int numberPage, int publicationYear, BookStatus status);

    // Getters
    int GetID() const;
    std::string GetTitle() const;
    std::string GetAuthor() const;
    std::vector<std::string> GetGenre() const;
    int GetNumberPage() const;
    int GetPublicationYear() const;
    BookStatus GetBookStatus() const;

    // Setters
    void SetTitle(const std::string& title);
    void SetAuthor(const std::string& author);
    void SetNumberPage(const int numberPage);
    void SetPublicationYear(const int publicationYear);
    void SetBookStatus(const std::string& statusStr);

    // Status to string
    bool isAvailable() const;
    std::string GetStatusString() const;
    static BookStatus stringtoStatus(const std::string& statusStr);

    // Display 
    void display() const;
};

#endif