#include "../include/Utlis.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace Utils {

bool isValidYear(int year) {
    // Books can't be from the future or too old
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* currentDate = std::localtime(&currentTime); // Fixed: &currentTime
    int currentYear = currentDate->tm_year + 1900;
    
    return (year > 0 && year <= currentYear);
}

bool isValidInteger(const std::string& str) {
    if (str.empty()) return false;
    
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c);
    });
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), 
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

void displayBooks(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "No books found." << std::endl;
        return;
    }
    
    // Header
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Author" 
              << std::setw(15) << "Genre" 
              << std::setw(6) << "Year" 
              << "Status" << std::endl;
    
    std::cout << std::string(80, '-') << std::endl;
    
    // Books
    for (const auto& book : books) {
        std::cout << std::left << std::setw(5) << book.getId() 
                  << std::setw(30) << (book.getTitle().length() > 27 ? 
                                       book.getTitle().substr(0, 27) + "..." : 
                                       book.getTitle())
                  << std::setw(20) << (book.getAuthor().length() > 17 ? 
                                       book.getAuthor().substr(0, 17) + "..." : 
                                       book.getAuthor())
                  << std::setw(15) << book.getGenre() 
                  << std::setw(6) << book.getPublicationYear() 
                  << (book.isBorrowed() ? "Borrowed" : "Available") << std::endl;
    }
}

void displayBookDetailed(const Book& book) {
    std::cout << "\nBook Details:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "ID: " << book.getId() << std::endl;
    std::cout << "Title: " << book.getTitle() << std::endl;
    std::cout << "Author: " << book.getAuthor() << std::endl;
    std::cout << "Genre: " << book.getGenre() << std::endl;
    std::cout << "Publication Year: " << book.getPublicationYear() << std::endl;
    std::cout << "Status: " << (book.isBorrowed() ? "Borrowed" : "Available") << std::endl;
    std::cout << std::string(40, '-') << std::endl;
}

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pauseExecution() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getPasswordInput() {
    std::string password;
    
    // Disable echo for password entry
    #ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    #else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    #endif
    
    std::getline(std::cin, password);
    
    // Restore echo
    #ifdef _WIN32
    SetConsoleMode(hStdin, mode);
    #else
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
    
    return password;
}

std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S"); // Fixed: &currentTime
    return ss.str();
}

std::string formatDate(int day, int month, int year) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << year << "-"
       << std::setw(2) << month << "-"
       << std::setw(2) << day;
    return ss.str();
}

} // namespace Utils