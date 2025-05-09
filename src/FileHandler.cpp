#include "../include/FileHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>

FileHandler::FileHandler(const std::string& filename) : dataFile(filename) {
    // Create data directory if it doesn't exist
    std::filesystem::path dir = std::filesystem::path(filename).parent_path();
    if (!dir.empty() && !std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }
}

bool FileHandler::saveBooks(const std::vector<Book>& books) {
    std::ofstream file(dataFile, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file for writing: " << dataFile << std::endl;
        return false;
    }
    
    // Save number of books first
    size_t size = books.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Save each book
    for (const auto& book : books) {
        int id = book.getId();
        int year = book.getPublicationYear();
        bool borrowed = book.isBorrowed();
        
        // Save book data
        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        
        // Save strings with size prefixes
        std::string title = book.getTitle();
        std::string author = book.getAuthor();
        std::string genre = book.getGenre();
        
        size_t titleLen = title.length();
        size_t authorLen = author.length();
        size_t genreLen = genre.length();
        
        file.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
        file.write(title.c_str(), titleLen);
        
        file.write(reinterpret_cast<const char*>(&authorLen), sizeof(authorLen));
        file.write(author.c_str(), authorLen);
        
        file.write(reinterpret_cast<const char*>(&genreLen), sizeof(genreLen));
        file.write(genre.c_str(), genreLen);
        
        file.write(reinterpret_cast<const char*>(&year), sizeof(year));
        file.write(reinterpret_cast<const char*>(&borrowed), sizeof(borrowed));
    }
    
    return file.good();
}

bool FileHandler::loadBooks(std::vector<Book>& books) {
    std::ifstream file(dataFile, std::ios::binary);
    if (!file) {
        // File might not exist yet, which is normal on first run
        if (!std::filesystem::exists(dataFile)) {
            return true; // Not an error, just no books yet
        }
        std::cerr << "Error: Cannot open file for reading: " << dataFile << std::endl;
        return false;
    }
    
    books.clear();
    
    // Read number of books
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Read each book
    for (size_t i = 0; i < size && file.good(); ++i) {
        int id, year;
        bool borrowed;
        std::string title, author, genre;
        
        // Read book ID
        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        
        // Read strings with size prefixes
        size_t titleLen, authorLen, genreLen;
        
        file.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));
        title.resize(titleLen);
        file.read(&title[0], titleLen);
        
        file.read(reinterpret_cast<char*>(&authorLen), sizeof(authorLen));
        author.resize(authorLen);
        file.read(&author[0], authorLen);
        
        file.read(reinterpret_cast<char*>(&genreLen), sizeof(genreLen));
        genre.resize(genreLen);
        file.read(&genre[0], genreLen);
        
        file.read(reinterpret_cast<char*>(&year), sizeof(year));
        file.read(reinterpret_cast<char*>(&borrowed), sizeof(borrowed));
        
        // Create book and add to the vector
        Book book(id, title, author, genre, year);
        if (borrowed) {
            book.borrowBook();
        }
        
        books.push_back(book);
    }
    
    return file.good() || file.eof();
}

bool FileHandler::createBackup(const std::string& backupFile) {
    // Check if source file exists
    if (!std::filesystem::exists(dataFile)) {
        std::cerr << "Error: Source file does not exist: " << dataFile << std::endl;
        return false;
    }
    
    // Create backup using C++ filesystem
    try {
        std::filesystem::path backupPath = backupFile;
        // Create directory for backup if it doesn't exist
        std::filesystem::path dir = backupPath.parent_path();
        if (!dir.empty() && !std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
        }
        
        std::filesystem::copy_file(
            dataFile, 
            backupFile, 
            std::filesystem::copy_options::overwrite_existing
        );
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating backup: " << e.what() << std::endl;
        return false;
    }
}

bool FileHandler::restoreFromBackup(const std::string& backupFile) {
    // Check if backup file exists
    if (!std::filesystem::exists(backupFile)) {
        std::cerr << "Error: Backup file does not exist: " << backupFile << std::endl;
        return false;
    }
    
    // Restore from backup using C++ filesystem
    try {
        std::filesystem::path dataPath = dataFile;
        // Create directory for data file if it doesn't exist
        std::filesystem::path dir = dataPath.parent_path();
        if (!dir.empty() && !std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
        }
        
        std::filesystem::copy_file(
            backupFile, 
            dataFile, 
            std::filesystem::copy_options::overwrite_existing
        );
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error restoring from backup: " << e.what() << std::endl;
        return false;
    }
}