# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Source and output
SRC := main.cpp
OBJ := main.o
OUT := main

INCLUDES := -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include

# Build target
all: $(OUT)

# Link
$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUT) $(OBJ)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all clean
