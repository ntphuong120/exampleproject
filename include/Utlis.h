#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "../include/Book.h" // Ensure Book.h defines the Book class

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace Utils {
    // Input validation
    bool isValidYear(int year);
    bool isValidInteger(const std::string& str);
    
    // String manipulation
    std::string trim(const std::string& str);
    std::string toLower(const std::string& str);
    
    // Book display
    void displayBooks(const std::vector<Book>& books);
    void displayBookDetailed(const Book& book);
    
    // Console utilities
    void clearScreen();
    void pauseExecution();
    std::string getPasswordInput();
    
    // Date and time
    std::string getCurrentDateTime();
    std::string formatDate(int day, int month, int year);
}

#endif