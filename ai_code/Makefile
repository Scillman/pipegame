# Makefile for PipeGame Vulkan application

CXX = g++ -I/redist/include
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
LDFLAGS = -L/redist/lib -lvulkan -lwayland-client -lSDL3

TARGET = pipegame
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean install-deps
