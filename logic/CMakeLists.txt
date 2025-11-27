# Compile all source files in logic/src recursively
file(GLOB_RECURSE LOGIC_SOURCES "src/*.cpp")

add_library(pacman_logic ${LOGIC_SOURCES})

# Expose include folders so Representation can see World.h, EntityModel.h, etc.
target_include_directories(pacman_logic PUBLIC
        include
        include/core
        include/entities
        include/world
)