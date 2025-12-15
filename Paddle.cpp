#include "Paddle.h"

void Paddle::handleInput(float windowWidth) {
    // sterowanie paletk¹
    if (Keyboard::isKeyPressed(Keyboard::Left))
        moveLeft();
    if (Keyboard::isKeyPressed(Keyboard::Right))
        moveRight();

    clampToBounds(windowWidth);
}