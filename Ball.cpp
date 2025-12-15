#include "Ball.h"

void Pilka::update(float width, float height, const Paddle& paddle) {
    move();
    collideWalls(width, height);
    collidePaddle(paddle);
    stopAtBottom(height);
}