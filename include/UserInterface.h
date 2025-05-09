#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "../include/Library.h"

class UserInterface {
private:
    Library& library;
    
    // Menu functions
    void displayMainMenu();
    void displayBookManagementMenu();
    void displaySearchMenu();
    void displayStatisticsMenu();
    void displayAdminMenu();
    
    // Book management
    void addBookUI();
    void removeBookUI();
    void updateBookUI();
    void borrowBookUI();
    void returnBookUI();
    
    // Search functionality
    void searchByIdUI();
    void searchByTitleUI();
    void searchByAuthorUI();
    void searchByGenreUI();
    void displayAllBooksUI();
    void displayAvailableBooksUI();
    void displayBorrowedBooksUI();
    
    // Admin functions
    void createBackupUI();
    void restoreBackupUI();
    bool verifyAdminPassword();
    
    // Helper methods
    int getIntegerInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    
public:
    UserInterface(Library& library);
    void start();
};

#endif // USERINTERFACE_H