CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
INCLUDES = -Iinclude
SOURCES = src/Book.cpp src/FileHandler.cpp src/Library.cpp src/UserInterface.cpp src/Main.cpp src/Utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = library_system

# Default target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
directories:
	mkdir -p data
	mkdir -p include
	mkdir -p src

# Clean up
clean:
	del /Q src\*.o $(TARGET).exe

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install the program (requires root privileges)
install: $(TARGET)
	copy $(TARGET).exe \usr\local\bin\

# Uninstall the program (requires root privileges)
uninstall:
	del \usr\local\bin\$(TARGET).exe

.PHONY: all clean run install uninstall directories