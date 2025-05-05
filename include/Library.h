// Định nghĩa lớp Library (tập hợp sách)

#ifndef LIBRARY_H
#define LIBRARY_H

#include "../include/Book.h"
#include <map>

class Library {
private:
    std::vector<Book> books;
    int nextID;
public:
    Library(std::vector<Book> books, int nextID);

    // Setters
    void add_book(int id, const std::string& title, const std::string& author, const std::vector<std::string> genre,
                int numberPage, int publicationYear, BookStatus status);
    void remove_book(int id);

    // feature
    void searchBook(const std::string& requirement) const;
};

#endif