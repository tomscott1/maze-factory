#include "maze_factory.h"
#include <iostream>

int main() {
    // Call the function and output the JSON string
    const char* json = generateObjectsJson();
    std::cout << "Generated JSON: " << json << std::endl;

    return 0;
}
