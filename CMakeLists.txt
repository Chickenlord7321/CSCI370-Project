cmake_minimum_required(VERSION 3.15)
project(myCrowApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Changes the default executable directory to the root directory, rather than build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Required packages
find_package(Crow CONFIG REQUIRED)

# Retrieve cpr
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3591f20e82338d0a21733045f59accd2d476d84f)
FetchContent_MakeAvailable(cpr)

# Executables
add_executable(goCrow src/main.cpp)
add_executable(addToCSV src/addToCSV.cpp)

target_link_libraries(goCrow PUBLIC Crow::Crow)
target_link_libraries(addToCSV PRIVATE cpr::cpr)
