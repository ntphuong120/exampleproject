#include "../include/Book.h"
#include <string>

Book::Book(int id, const std::string& title, const std::string& author, const std::vector<std::string>& genre,
        int numberPage, int publicationYear, BookStatus status) 
        : id(id), title(title), author(author), genre(genre), numberPage(numberPage), 
        publicationYear(publicationYear), status(status) {}

// Getters
int Book::GetID() const {
        return id;
}
std::string Book::GetTitle() const {
        return title;
}
std::string Book::GetAuthor() const {
        return author;
}
std::vector<std::string> Book::GetGenre() const {
        return genre;
}
int Book::GetNumberPage() const {
        return numberPage;
}
int Book::GetPublicationYear() const {
        return publicationYear;
}
BookStatus Book::GetBookStatus() const {
        return status;
}

bool Book::isAvailable() const {
        if (status == BookStatus::AVAILABLE) return true;
        return false;
}

// Setters
void Book::SetTitle(const std::string& title) {
        this->title = title;
}
void Book::SetAuthor(const std::string& author) {
        this->author = author;
}
void Book::SetNumberPage(int numberPage) {
        this->numberPage = numberPage;
}
void Book::SetPublicationYear(int publicationYear) {
        this->publicationYear = publicationYear;
}
void Book::SetBookStatus(const std::string& statusStr) {
        this->status = stringtoStatus(statusStr);
}

std::string Book::GetStatusString() const {
        switch (status) 
        {
        case BookStatus::UNAVAILABLE:
                return "UNAVAILABLE";
        case BookStatus::AVAILABLE:
                return "AVAILABLE";
        case BookStatus::UNREAD:
                return "UNREAD";
        case BookStatus::ONGOING:
                return "ONGOING";
        case BookStatus::DONE:
                return "DONE";
        default:
                return "UNKNOWN";
        }
}

BookStatus Book::stringtoStatus(const std::string& statusStr) {
        if (statusStr == "Available" || statusStr == "AVAILBLE") {
                return BookStatus::AVAILABLE;
        } else if (statusStr == "Unavailable" || statusStr == "UNAVAILABLE") {
                return BookStatus::UNAVAILABLE;
        } else if (statusStr == "Unread" || statusStr == "UNREAD") {
                return BookStatus::UNREAD;
        } else if (statusStr == "Ongoing" || statusStr == "ONGOING") {
                return BookStatus::ONGOING;
        } else if (statusStr == "Done" || statusStr == "DONE") {
                return BookStatus::DONE;
        } else {
                return BookStatus::AVAILABLE;
        }
}

void Book::display() const {
        if (Book::isAvailable() == true) {
                std::cout << "ID: " << id << std::endl;
                std::cout << "Title: " << title << std::endl;
                std::cout << "Author" << author << std::endl;
                std::cout << "Genre: ";
                for (const std::string& type : genre) {
                        std::cout << type << ' ';
                } std::cout << std::endl;
                std::cout << "Numer Of Pages:" << numberPage << std::endl;
                std::cout << "Publication Year: " << publicationYear << std::endl;
                std::cout << "Status: " << GetStatusString() << std::endl << std::endl;
        }
}