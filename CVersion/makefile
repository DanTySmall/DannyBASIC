# Makefile for DannyBasic Compiler
# Compiler for TinyBasic made by Daniel Small

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
TARGET = dannybasic

# Source files
SOURCES = DannyBasic.cpp Parse.cpp Syntax.cpp Execute.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Parse.h Syntax.hpp Execute.hpp

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET) output.dyb

# Install target (optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall target (optional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Run target for testing
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Create a test program
test: $(TARGET)
	@echo "10 PRINT \"Hello, World!\"" > test.bas
	@echo "20 END" >> test.bas
	./$(TARGET) test.bas

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the DannyBasic compiler (default)"
	@echo "  clean    - Remove object files and executable"
	@echo "  debug    - Build with debug symbols"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  run      - Run the compiler (prompts for file)"
	@echo "  test     - Create and run a simple test program"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean install uninstall run debug test help
