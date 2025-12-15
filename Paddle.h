#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
using namespace sf;

class Paddle {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float predkosc;
	RectangleShape shape;

public:
	Paddle(float startX, float startY, float width, float height, float speed) {
		x = startX;
		y = startY;
		szerokosc = width;
		wysokosc = height;
		predkosc = speed;
		shape.setSize(Vector2f(szerokosc, wysokosc));
		shape.setOrigin(szerokosc / 2, wysokosc / 2);
		shape.setPosition(x, y);
		shape.setFillColor(Color::White);	
	}

	void moveLeft() {
		x -= predkosc;
		shape.setPosition(x, y);
	}
	void moveRight() {
		x += predkosc;
		shape.setPosition(x, y);
	}

	void clampToBounds(float width) {
		if (x - szerokosc / 2 < 0) {
			x = szerokosc / 2;
		}
		if (szerokosc / 2 + x > width) {
			x = width - szerokosc / 2;
		}
	}
	
	void handleInput(float windowWidth);

	float getX() const { return x; }
	float getY() const { return y; }
	float getWidth() const { return szerokosc; }
	float getHeight() const { return wysokosc; }
	const RectangleShape& getShape() const { return shape; }
};

