#umanskyvivian@gmail.com
CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -fPIC -Wno-deprecated-enum-enum-conversion `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets`
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99 --suppressions=qt.supp

SOURCES_MAIN = main.cpp demo.cpp
OBJECTS_MAIN = $(SOURCES_MAIN:.cpp=.o)

SOURCES_TEST = TestCounter.cpp test.cpp
OBJECTS_TEST = $(SOURCES_TEST:.cpp=.o)

EXECUTABLE_MAIN = TreeVisualizer
EXECUTABLE_TEST = test


all: tree tests

tree: $(EXECUTABLE_MAIN)
	./$(EXECUTABLE_MAIN)

$(EXECUTABLE_MAIN): $(OBJECTS_MAIN)
	$(CXX) $(OBJECTS_MAIN) -o $@ $(LDFLAGS)

# Tests
tests: $(EXECUTABLE_TEST)
	./$(EXECUTABLE_TEST)

$(EXECUTABLE_TEST): $(OBJECTS_TEST)
	$(CXX) $(OBJECTS_TEST) -o $@ $(LDFLAGS)

valgrind: $(EXECUTABLE_TEST)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(EXECUTABLE_TEST) 2>&1 | { egrep "lost| at " || true; }


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJECTS_MAIN) $(OBJECTS_TEST) $(EXECUTABLE_MAIN) $(EXECUTABLE_TEST)
