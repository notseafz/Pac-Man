# Compile all source files in logic/src recursively
file(GLOB_RECURSE LOGIC_SOURCES "src/*.cpp")

add_library(pacman_logic ${LOGIC_SOURCES}
        include/entities/EntityModel.h
        include/entities/Wall.h
        include/AbstractFactory.h
        include/entities/PacMan.h
        src/core/Stopwatch.cpp
        include/core/Stopwatch.h
        include/core/Observer.h
        include/core/Subject.h
        include/entities/Collectable.h
        include/entities/Coin.h
        include/core/Score.h
        src/core/Score.cpp
)

# Expose include folders so Representation can see World.h, EntityModel.h, etc.
target_include_directories(pacman_logic PUBLIC
        include
        include/core
        include/entities
        include/world
)