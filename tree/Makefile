CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
TARGET := find_k_in_binary_tree_test
SRCS := find_k_in_binary_tree.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean