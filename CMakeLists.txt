cmake_minimum_required(VERSION 3.15)
project(myCrowApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Required packages
find_package(Crow REQUIRED)

# Executable
add_executable(go src/main.cpp)

target_link_libraries(go Crow::Crow)
