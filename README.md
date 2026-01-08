# Pac-Man (C++ / SFML)

**Student Name:** Ahjmed Meiyaki
**Student ID:** 20243666
**Course:** Advanced Programming 2025-2026

## Overview
A recreation of the classic arcade game Pac-Man, built using **C++20** and **SFML**.

## Features
*   **MVC Architecture:** Logic library is independent of SFML.
*   **Smart AI:** Ghosts use Manhattan Distance pathfinding with unique behaviors (Chase, Ambush, Random).
*   **Game States:** Menu, Gameplay, Victory, and Game Over states.
*   **Core Mechanics:** Collision detection, grid snapping, and difficulty scaling.
*   **Memory Safety:** Validated with Valgrind (0 memory leaks) using smart pointers.

## Design Patterns
*   **Abstract Factory:** Decouples entity creation from specific rendering implementations.
*   **Observer:** Updates the View when the Model changes state without tight coupling.
*   **State:** Manages transitions between different game screens.
*   **Singleton:** Provides global access to the Score manager and Stopwatch.

## Build Instructions

**Prerequisites:** CMake 3.28+, GCC/Clang (C++20), SFML 2.6.1.

```bash
# 1. Clone repository
git clone https://github.com/notseafz/PacMan-Project.git
cd PacMan-Project

# 2. Build
mkdir build
cd build
cmake ..
make

# 3. Run
./PacManGame
