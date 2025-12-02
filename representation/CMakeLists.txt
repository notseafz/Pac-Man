find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Compile all source files in representation/src recursively
file(GLOB_RECURSE REP_SOURCES "src/*.cpp")

add_library(pacman_representation ${REP_SOURCES}
        src/ConcreteFactory.cpp
        include/ConcreteFactory.h
        include/Camera.h
        include/views/EntityView.h
        include/views/PacmanView.h)

# Link Logic and SFML
target_link_libraries(pacman_representation
        PUBLIC
        pacman_logic
        sfml-graphics sfml-window sfml-system sfml-audio
)

target_include_directories(pacman_representation PUBLIC
        include
        include/states
        include/views
        include/factory
)