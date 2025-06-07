CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Wno-sign-compare

TARGET := lru_cache_test
SRC := lru_cache.cpp
OBJ := $(SRC:.cpp=.o)

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)