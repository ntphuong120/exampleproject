#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "../include/Book.h"

class FileHandler {
private:
    std::string dataFile;
    
public:
    FileHandler(const std::string& filename = "data/Book.dat");
    
    // File operations
    bool saveBooks(const std::vector<Book>& books);
    bool loadBooks(std::vector<Book>& books);
    
    // Backup and restore
    bool createBackup(const std::string& backupFile);
    bool restoreFromBackup(const std::string& backupFile);
};

#endif // FILEHANDLER_H