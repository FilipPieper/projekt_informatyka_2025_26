#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"

// forward declaration
class Pilka;

class Bricks {
private:
    std::vector<Brick> m_bricks;

public:
    // tworzy poziom (to co by³o w resetGame)
    void buildLevel(float screenWidth);

    // kolizja pi³ki z klockami
    void collide(Pilka& ball, int& destroyedCounter);

    // rysowanie
    void draw(sf::RenderWindow& window);

    // pomocnicze
    bool empty() const;
    void clear();

    std::vector<Brick>& data();
    const std::vector<Brick>& data() const;

 

};
