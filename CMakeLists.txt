# Author: Caleb Bronn
# Last update: 4 Apr 2025

cmake_minimum_required(VERSION 3.7)
project(MovieReviewApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Changes the default executable directory to the root directory, rather than build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Retrieve cpr
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3591f20e82338d0a21733045f59accd2d476d84f)
FetchContent_MakeAvailable(cpr)

# Executables
add_executable(addMovies src/addMovies.cpp)

# Link C++ Requests Library
target_link_libraries(addMovies PRIVATE cpr::cpr)
