cmake_minimum_required(VERSION 3.10)
project(maze-factory)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the include directories
include_directories(include)

# Create a static library from the source files
add_library(maze-factory SHARED src/maze_factory.cpp)

# Optionally, if you want to create a main executable for testing
add_executable(maze-factory-app src/main.cpp)
target_link_libraries(maze-factory-app maze-factory)