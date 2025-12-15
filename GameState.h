#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Bricks.h"
#include <fstream>


struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
	sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    void capture(const Paddle& paletka, const Pilka& pilka, const Bricks& bloki);
    bool saveToFile(const std::string& filename);

    bool loadFromFile(const std::string& filename,
        Paddle& paletka, Pilka& pilka,
        Bricks& bloki);
};