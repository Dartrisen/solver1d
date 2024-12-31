CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRC = main.cpp src/time_integrator.cpp src/equation.cpp src/grid.cpp
INCLUDE = -Iinclude
OBJS = $(SRC:src/%.cpp=build/%.o)
TARGET = main

all: build

build: $(TARGET)
	$(MAKE) clean-objects

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

# Rule to create object files from source files
build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean the object files and remove the build directory
clean-objects:
	rm -rf build

# Clean the target
clean: clean-objects
	rm -f $(TARGET)

.PHONY: all build clean clean-objects