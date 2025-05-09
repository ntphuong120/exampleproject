#include "../include/Library.h"
#include "../include/UserInterface.h"
#include "../include/Utlis.h"
#include <iostream>

int main() {
    try {
        // Initialize the library with default data file path
        Library library;
        
        // Create and start the user interface
        UserInterface ui(library);
        ui.start();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }
    
    return 0;
}