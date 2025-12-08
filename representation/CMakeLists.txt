find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Compile all source files in representation/src recursively
file(GLOB_RECURSE REP_SOURCES "src/*.cpp")

add_library(pacman_representation ${REP_SOURCES}
        src/ConcreteFactory.cpp
        include/ConcreteFactory.h
        include/Camera.h
        include/views/EntityView.h
        include/views/PacmanView.h
        include/states/State.h
        include/states/StateManager.h
        src/states/StateManager.cpp
        include/states/MenuState.h
        src/states/MenuState.cpp
        include/states/VictoryState.h
        src/states/VictoryState.cpp
        include/states/LevelState.h
        src/states/LevelState.cpp)

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