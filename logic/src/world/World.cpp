#include "world/World.h"
#include "entities/Wall.h"
#include "entities/PacMan.h"
#include "core/Stopwatch.h"
#include "Coin.h"
#include "Score.h"
#include "Ghost.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

namespace Logic {
    World::World(std::shared_ptr<AbstractFactory> initFactory) : factory(initFactory) {
        std::cout << "[Logic] World initialized." << std::endl;

        std::string filename = "assets/maps/map3.txt";
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "ERROR: Could not open " << filename << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        if (lines.empty()) return;

        int rows = lines.size();
        int cols = lines[0].size();


        float tileWidth = 2.0f / cols;
        float tileHeight = tileWidth * (800.0f / 600.0f);

        float totalMapHeight = rows * tileHeight;
        float startY = totalMapHeight / 2.0f;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (c >= lines[r].size()) break;
                char tile = lines[r][c];

                float x = -1.0f + (c * tileWidth) + (tileWidth / 2.0f);

                float y = startY - (r * tileHeight) - (tileHeight / 2.0f);

                if (tile == '#') {
                    auto wall = factory->createWall(x, y, tileWidth, tileHeight);
                    entities.push_back(wall);
                    walls.push_back(wall);
                }
                else if (tile == 'P') {
                    pacman = factory->createPacMan(x,y, tileWidth, tileHeight);
                    pacman->setMapOriginY(startY);
                    entities.push_back(pacman);

                }
                else if (tile == '.') {
                    auto coin = factory->createCoin(x, y);
                    entities.push_back(coin);
                    coins.push_back(coin);
                }
                else if (tile == 'G') {
                    auto ghost = factory->createGhost(x, y, tileWidth, tileHeight);
                    ghost->setMapOriginY(startY);
                    entities.push_back(ghost);
                    ghosts.push_back(ghost);

                }
            }
        }
        std::cout << "[Logic] Map Loaded." << std::endl;
    }

    void World::update() {
        Stopwatch::getInstance().tick();
        float dt = Stopwatch::getInstance().getDeltaTime();

        if (pacman) {
            pacman->update(dt, walls);
        }
        float pacmanX = pacman->getX();
        float pacmanY = pacman->getY();

        float eatDistance = pacman->getWidth() / 2.0f;

        for (auto& coin : coins) {
            if (coin->getIsCollected()){
                continue;
            }

            float dx = std::abs(pacmanX - coin->getX());
            float dy = std::abs(pacmanY - coin->getY());

            if (dx < eatDistance and dy < eatDistance) {
                coin->collect();
                Score::getInstance().addScore(coin->getScoreValue());
            }

        }

        for (auto& ghost : ghosts) {
            ghost->update(dt, walls);
        }
    }
}