//umanskyvivian@gmail.com
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include <stdlib.h>
#include <cstdlib>
void runDemo();

using namespace std;

int main()

{
    setenv("QT_QPA_PLATFORM", "xcb", 1);
    std::cout << "Running demo..." << std::endl;
    runDemo(); // Run the demo functionality
}