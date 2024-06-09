# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I. -I/mingw64/include/SDL2

# Linker flags
LDFLAGS = -L/mingw64/lib -lSDL2 -lSDL2main -mconsole

# Executable name
TARGET = main

# Source files
SRCS = main.cpp GameLoop.cpp

# Object files (derived from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target: build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target: remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
