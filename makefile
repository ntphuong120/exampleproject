# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I include

# Directories
SRCDIR = src
INCLUDEDIR = include
BUILDDIR = build
BINDIR = bin
DATADIR = data

# Target executable
TARGET = $(BINDIR)/library_system

# Source and object files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
HEADERS := $(wildcard $(INCLUDEDIR)/*.h)

# Default target
all: directories $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build successful! Run ./$(TARGET) to start the application."

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create necessary directories
directories:
	@mkdir -p $(BUILDDIR) $(BINDIR) $(DATADIR)

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(BINDIR)
	@echo "Clean completed!"

# Run the application
run: all
	./$(TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build files"
	@echo "  run       - Build and run the application"
	@echo "  help      - Display this help message"

.PHONY: all clean run help directories