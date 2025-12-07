#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"


class Pilka {
private:
    float x;
    float y;
    float vx;
    float vy;
    float radius;

public:
    sf::CircleShape shape;

    Pilka(float startX, float startY, float velX, float velY, float r)
        : x(startX), y(startY), vx(velX), vy(velY), radius(r)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }

    void bounceX() { vx = -vx; }
    void bounceY() { vy = -vy; }

    void collideWalls(float width, float height) {
        if (x - radius <= 0) {
            x = radius;
            bounceX();
        }
        else if (x + radius >= width) {
            x = width - radius;
            bounceX();
        }

        if (y - radius <= 0) {
            y = radius;
            bounceY();
        }
    }

    void stopAtBottom(float height) {
        if (y + radius >= height) {
            y = height - radius;
            vx = 0;
            vy = 0;
            shape.setPosition(x, y);
        }
    }

    bool collidePaddle(const Paddle& p) {
        float palX = p.getX();
        float palY = p.getY();
        float palW = p.getWidth();
        float palH = p.getHeight();

        bool overlappedX =
            (x + radius >= palX - palW / 2.f) &&
            (x - radius <= palX + palW / 2.f);

        bool overlappedY =
            (y + radius >= palY - palH / 2.f) &&
            (y - radius <= palY + palH / 2.f);

        if (overlappedX && overlappedY) {
            vy = -std::abs(vy);                // odbicie w górê
            y = (palY - palH / 2.f) - radius;   // wyjêcie pi³ki nad paletkê
            shape.setPosition(x, y);
            return true;
        }

        return false;
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }

  
    const sf::CircleShape& getShape() const { return shape; }
};
