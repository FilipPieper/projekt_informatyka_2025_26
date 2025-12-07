#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
private:
    int punkty_zycia;
    bool jestZniszczony;
    static const std::array<sf::Color, 4> colorLUT;



public:
    Brick(sf::Vector2f startPosition, sf::Vector2f size, int L) {
        // ręczne "clampowanie"
        if (L < 0) punkty_zycia = 0;
        else if (L > 3) punkty_zycia = 3;
        else punkty_zycia = L;

        jestZniszczony = (punkty_zycia == 0);

        this->setSize(size);
        this->setPosition(startPosition);
      

        // jeśli cegła od razu ma 0 punktów życia -> ustawiamy transparent
        if (jestZniszczony)
            this->setFillColor(sf::Color::Transparent);
        else
            aktualizujKolor();
    }

    void trafienie() {
        if (jestZniszczony)
            return;

        punkty_zycia--;
        if (punkty_zycia <= 0) {
            jestZniszczony = true;
            this->setFillColor(sf::Color::Transparent);
        }
        else {
            aktualizujKolor();
        }
    }

    void aktualizujKolor() {
        if (punkty_zycia > 0 && punkty_zycia <= (int)colorLUT.size())
            this->setFillColor(colorLUT[punkty_zycia - 1]);
        else if (punkty_zycia <= 0)
            this->setFillColor(sf::Color::Transparent);
    }

    bool czyZniszczony() const { return jestZniszczony; }
    bool widoczna() const { return !jestZniszczony; }

	int getHp() const { return punkty_zycia; }
};

// Definicja tablicy kolorów (1 życie -> Red, 2 -> Green, 3 -> Blue, 4 -> Transparent)
inline const std::array<sf::Color, 4> Brick::colorLUT = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Transparent
};
