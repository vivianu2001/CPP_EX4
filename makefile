# Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = main

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

main.o: main.cpp tree.hpp node.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) *.o
