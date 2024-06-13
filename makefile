# Makefile

CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -fPIC -Wno-deprecated-enum-enum-conversion `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets`
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = TreeVisualizer

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
