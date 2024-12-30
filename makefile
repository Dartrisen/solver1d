CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp grid.cpp equation.cpp time_integrator.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = main

all: build

build: $(TARGET)
	$(MAKE) clean-objects

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: clean-objects
	rm -f $(TARGET)

clean-objects:
	rm -f $(OBJS)

.PHONY: all build clean clean-objects