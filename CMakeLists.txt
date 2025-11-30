cmake_minimum_required(VERSION 3.22)
project(PacManGame VERSION 1.0 LANGUAGES CXX)

# Enforce C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

# Add the library subdirectories
add_subdirectory(logic)
add_subdirectory(representation)

# Create the Executable
add_executable(PacManGame src/main.cpp)

# Link the executable to Representation
target_link_libraries(PacManGame PRIVATE pacman_representation)

# Copy assets to the build folder automatically
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})