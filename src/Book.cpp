#include "../include/Book.h"
#include <sstream>

Book::Book() : id(0), title(""), author(""), genre(""), publicationYear(0), borrowed(false) {}

Book::Book(int id, const std::string& title, const std::string& author, 
           const std::string& genre, int publicationYear) 
    : id(id), title(title), author(author), genre(genre), 
      publicationYear(publicationYear), borrowed(false) {}

// Getters
int Book::getId() const {
    return id;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getGenre() const {
    return genre;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

bool Book::isBorrowed() const {
    return borrowed;
}

// Setters
void Book::setId(int id) {
    this->id = id;
}

void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setGenre(const std::string& genre) {
    this->genre = genre;
}

void Book::setPublicationYear(int year) {
    this->publicationYear = year;
}

// Book status
void Book::borrowBook() {
    borrowed = true;
}

void Book::returnBook() {
    borrowed = false;
}

// String representation
std::string Book::toString() const {
    std::stringstream ss;
    ss << "ID: " << id << "\n"
       << "Title: " << title << "\n"
       << "Author: " << author << "\n"
       << "Genre: " << genre << "\n"
       << "Publication Year: " << publicationYear << "\n"
       << "Status: " << (borrowed ? "Borrowed" : "Available") << "\n";
    return ss.str();
}