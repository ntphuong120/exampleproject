#include "../include/UserInterface.h"
#include "../include/Utlis.h"
#include <iostream>
#include <limits>
#include <string>
#include <algorithm>

// Constructor
UserInterface::UserInterface(Library& lib) : library(lib) {}

// Starting point of the UI
void UserInterface::start() {
    int choice;
    bool running = true;

    while (running) {
        Utils::clearScreen();
        displayMainMenu();

        choice = getIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1: // Book Management
                displayBookManagementMenu();
                break;
            case 2: // Search for Books
                displaySearchMenu();
                break;
            case 3: // View Statistics
                displayStatisticsMenu();
                break;
            case 4: // Admin Options
                displayAdminMenu();
                break;
            case 0: // Exit
                running = false;
                std::cout << "\nThank you for using the Library Management System!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                Utils::pauseExecution();
        }
    }
}

// Menu displays
void UserInterface::displayMainMenu() {
    std::cout << "=======================================" << std::endl;
    std::cout << "      LIBRARY MANAGEMENT SYSTEM       " << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "1. Book Management" << std::endl;
    std::cout << "2. Search for Books" << std::endl;
    std::cout << "3. View Statistics" << std::endl;
    std::cout << "4. Admin Options" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=======================================" << std::endl;
}

void UserInterface::displayBookManagementMenu() {
    int choice;
    bool submenu = true;
    
    while (submenu) {
        Utils::clearScreen();
        std::cout << "=======================================" << std::endl;
        std::cout << "          BOOK MANAGEMENT             " << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "1. Add a New Book" << std::endl;
        std::cout << "2. Remove a Book" << std::endl;
        std::cout << "3. Update Book Details" << std::endl;
        std::cout << "4. Borrow a Book" << std::endl;
        std::cout << "5. Return a Book" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "=======================================" << std::endl;
        
        choice = getIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                addBookUI();
                break;
            case 2:
                removeBookUI();
                break;
            case 3:
                updateBookUI();
                break;
            case 4:
                borrowBookUI();
                break;
            case 5:
                returnBookUI();
                break;
            case 0:
                submenu = false;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                Utils::pauseExecution();
        }
    }
}

void UserInterface::displaySearchMenu() {
    int choice;
    bool submenu = true;
    
    while (submenu) {
        Utils::clearScreen();
        std::cout << "=======================================" << std::endl;
        std::cout << "           SEARCH BOOKS               " << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "1. Search by ID" << std::endl;
        std::cout << "2. Search by Title" << std::endl;
        std::cout << "3. Search by Author" << std::endl;
        std::cout << "4. Search by Genre" << std::endl;
        std::cout << "5. View All Books" << std::endl;
        std::cout << "6. View Available Books" << std::endl;
        std::cout << "7. View Borrowed Books" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "=======================================" << std::endl;
        
        choice = getIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                searchByIdUI();
                break;
            case 2:
                searchByTitleUI();
                break;
            case 3:
                searchByAuthorUI();
                break;
            case 4:
                searchByGenreUI();
                break;
            case 5:
                displayAllBooksUI();
                break;
            case 6:
                displayAvailableBooksUI();
                break;
            case 7:
                displayBorrowedBooksUI();
                break;
            case 0:
                submenu = false;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                Utils::pauseExecution();
        }
    }
}

void UserInterface::displayStatisticsMenu() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          LIBRARY STATISTICS          " << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "Total Books: " << library.getTotalBooks() << std::endl;
    std::cout << "Available Books: " << library.getAvailableBooks() << std::endl;
    std::cout << "Borrowed Books: " << library.getBorrowedBooks() << std::endl;
    std::cout << "=======================================" << std::endl;
    
    Utils::pauseExecution();
}

void UserInterface::displayAdminMenu() {
    if (!verifyAdminPassword()) {
        std::cout << "\nIncorrect password. Access denied." << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    int choice;
    bool submenu = true;
    
    while (submenu) {
        Utils::clearScreen();
        std::cout << "=======================================" << std::endl;
        std::cout << "           ADMIN OPTIONS              " << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "1. Create Backup" << std::endl;
        std::cout << "2. Restore from Backup" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "=======================================" << std::endl;
        
        choice = getIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                createBackupUI();
                break;
            case 2:
                restoreBackupUI();
                break;
            case 0:
                submenu = false;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                Utils::pauseExecution();
        }
    }
}

// Book management implementations
void UserInterface::addBookUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "            ADD NEW BOOK              " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string title = getStringInput("Enter book title: ");
    std::string author = getStringInput("Enter author name: ");
    std::string genre = getStringInput("Enter genre: ");
    int year = getIntegerInput("Enter publication year: ");
    
    if (!Utils::isValidYear(year)) {
        std::cout << "\nInvalid year. Please enter a valid year." << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    if (library.addBook(title, author, genre, year)) {
        std::cout << "\nBook added successfully!" << std::endl;
    } else {
        std::cout << "\nFailed to add book. Please try again." << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::removeBookUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "            REMOVE BOOK               " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    int id = getIntegerInput("Enter book ID to remove: ");
    
    Book* book = library.findBookById(id);
    if (!book) {
        std::cout << "\nBook not found with ID: " << id << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    Utils::displayBookDetailed(*book);
    std::cout << "\nAre you sure you want to remove this book? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (Utils::toLower(confirm) == "y" || Utils::toLower(confirm) == "yes") {
        if (library.removeBook(id)) {
            std::cout << "\nBook removed successfully!" << std::endl;
        } else {
            std::cout << "\nFailed to remove book. Please try again." << std::endl;
        }
    } else {
        std::cout << "\nBook removal cancelled." << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::updateBookUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          UPDATE BOOK DETAILS         " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    int id = getIntegerInput("Enter book ID to update: ");
    
    Book* book = library.findBookById(id);
    if (!book) {
        std::cout << "\nBook not found with ID: " << id << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    Utils::displayBookDetailed(*book);
    
    std::cout << "\nEnter new details (leave blank to keep current values):" << std::endl;
    
    std::string title = getStringInput("Enter new title [" + book->getTitle() + "]: ");
    std::string author = getStringInput("Enter new author [" + book->getAuthor() + "]: ");
    std::string genre = getStringInput("Enter new genre [" + book->getGenre() + "]: ");
    
    std::string yearStr = getStringInput("Enter new publication year [" + 
                                          std::to_string(book->getPublicationYear()) + "]: ");
    int year = 0;
    if (!yearStr.empty()) {
        if (Utils::isValidInteger(yearStr)) {
            year = std::stoi(yearStr);
            if (!Utils::isValidYear(year)) {
                std::cout << "\nInvalid year. This field will not be updated." << std::endl;
                year = 0;
            }
        } else {
            std::cout << "\nInvalid year format. This field will not be updated." << std::endl;
        }
    }
    
    if (library.updateBook(id, title, author, genre, year)) {
        std::cout << "\nBook updated successfully!" << std::endl;
    } else {
        std::cout << "\nFailed to update book. Please try again." << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::borrowBookUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "            BORROW BOOK               " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    int id = getIntegerInput("Enter book ID to borrow: ");
    
    Book* book = library.findBookById(id);
    if (!book) {
        std::cout << "\nBook not found with ID: " << id << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    if (book->isBorrowed()) {
        std::cout << "\nThis book is already borrowed." << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    Utils::displayBookDetailed(*book);
    
    std::cout << "\nConfirm borrowing this book? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (Utils::toLower(confirm) == "y" || Utils::toLower(confirm) == "yes") {
        if (library.borrowBook(id)) {
            std::cout << "\nBook borrowed successfully!" << std::endl;
        } else {
            std::cout << "\nFailed to borrow book. Please try again." << std::endl;
        }
    } else {
        std::cout << "\nBook borrowing cancelled." << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::returnBookUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "            RETURN BOOK               " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    int id = getIntegerInput("Enter book ID to return: ");
    
    Book* book = library.findBookById(id);
    if (!book) {
        std::cout << "\nBook not found with ID: " << id << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    if (!book->isBorrowed()) {
        std::cout << "\nThis book is not currently borrowed." << std::endl;
        Utils::pauseExecution();
        return;
    }
    
    Utils::displayBookDetailed(*book);
    
    std::cout << "\nConfirm returning this book? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (Utils::toLower(confirm) == "y" || Utils::toLower(confirm) == "yes") {
        if (library.returnBook(id)) {
            std::cout << "\nBook returned successfully!" << std::endl;
        } else {
            std::cout << "\nFailed to return book. Please try again." << std::endl;
        }
    } else {
        std::cout << "\nBook return cancelled." << std::endl;
    }
    
    Utils::pauseExecution();
}

// Search functionality implementations
void UserInterface::searchByIdUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "           SEARCH BY ID               " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    int id = getIntegerInput("Enter book ID to search: ");
    
    Book* book = library.findBookById(id);
    if (book) {
        Utils::displayBookDetailed(*book);
    } else {
        std::cout << "\nNo book found with ID: " << id << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::searchByTitleUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          SEARCH BY TITLE             " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string title = getStringInput("Enter title to search: ");
    
    auto books = library.findBooksByTitle(title);
    
    std::cout << "\nSearch Results (" << books.size() << " books found):" << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

void UserInterface::searchByAuthorUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          SEARCH BY AUTHOR            " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string author = getStringInput("Enter author name to search: ");
    
    auto books = library.findBooksByAuthor(author);
    
    std::cout << "\nSearch Results (" << books.size() << " books found):" << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

void UserInterface::searchByGenreUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          SEARCH BY GENRE             " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string genre = getStringInput("Enter genre to search: ");
    
    auto books = library.findBooksByGenre(genre);
    
    std::cout << "\nSearch Results (" << books.size() << " books found):" << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

void UserInterface::displayAllBooksUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "            ALL BOOKS                 " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    const auto& books = library.getAllBooks();
    
    std::cout << "\nTotal Books: " << books.size() << std::endl << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

void UserInterface::displayAvailableBooksUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          AVAILABLE BOOKS             " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    auto books = library.getAvailableBooksList();
    
    std::cout << "\nAvailable Books: " << books.size() << std::endl << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

void UserInterface::displayBorrowedBooksUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "          BORROWED BOOKS              " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    auto books = library.getBorrowedBooksList();
    
    std::cout << "\nBorrowed Books: " << books.size() << std::endl << std::endl;
    Utils::displayBooks(books);
    
    Utils::pauseExecution();
}

// Admin functions
void UserInterface::createBackupUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "           CREATE BACKUP              " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string timestamp = Utils::getCurrentDateTime();
    timestamp.erase(std::remove_if(timestamp.begin(), timestamp.end(), 
                     [](char c) { return c == ':' || c == ' '; }), timestamp.end());
    
    std::string backupFile = "data/backup_" + timestamp + ".dat";
    
    if (library.createBackup(backupFile)) {
        std::cout << "\nBackup created successfully: " << backupFile << std::endl;
    } else {
        std::cout << "\nFailed to create backup. Please try again." << std::endl;
    }
    
    Utils::pauseExecution();
}

void UserInterface::restoreBackupUI() {
    Utils::clearScreen();
    std::cout << "=======================================" << std::endl;
    std::cout << "         RESTORE FROM BACKUP          " << std::endl;
    std::cout << "=======================================" << std::endl;
    
    std::string backupFile = getStringInput("Enter backup file path (e.g., data/backup_20250509.dat): ");
    
    std::cout << "\nWARNING: Restoring from backup will replace all current data!" << std::endl;
    std::cout << "Are you sure you want to continue? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (Utils::toLower(confirm) == "y" || Utils::toLower(confirm) == "yes") {
        if (library.restoreFromBackup(backupFile)) {
            std::cout << "\nBackup restored successfully!" << std::endl;
        } else {
            std::cout << "\nFailed to restore from backup. Please check the file path and try again." << std::endl;
        }
    } else {
        std::cout << "\nRestore operation cancelled." << std::endl;
    }
    
    Utils::pauseExecution();
}

bool UserInterface::verifyAdminPassword() {
    std::cout << "\nEnter admin password: ";
    std::string password = Utils::getPasswordInput();
    
    // Simple password for demonstration purposes
    // In a real system, use secure password storage and verification
    return password == "admin123";
}

// Helper methods
int UserInterface::getIntegerInput(const std::string& prompt) {
    std::string input;
    int value = 0;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        try {
            if (input.empty()) {
                value = 0;
                validInput = true;
            } else if (Utils::isValidInteger(input)) {
                value = std::stoi(input);
                validInput = true;
            } else {
                std::cout << "Invalid input. Please enter a number." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error processing input. Please try again." << std::endl;
        }
    }
    
    return value;
}

std::string UserInterface::getStringInput(const std::string& prompt) {
    std::string input;
    
    std::cout << prompt;
    std::getline(std::cin, input);
    
    return Utils::trim(input);
}