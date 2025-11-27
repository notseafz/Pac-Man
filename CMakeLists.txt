cmake_minimum_required(VERSION 3.28)
project(PacManGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

# Add Libraries
add_subdirectory(logic)
add_subdirectory(representation)

# Main Executable
add_executable(PacManGame src/main.cpp)
target_link_libraries(PacManGame PRIVATE pacman_representation)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})