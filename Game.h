#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Bricks.h"
#include "Menu.h"
#include "GameState.h"
#include "Scoreboard.h"

using namespace sf;

class Game {
private:
    enum class State {
        MenuState,
        PlayingState,
        ScoresState,
        LoadState,
        ExitState
    };

    RenderWindow m_window;
    Clock m_deltaClock;

    Paddle m_paletka;
    Pilka m_pilka;
    Bricks m_bricks;

    Menu m_menu;         
    State m_state;       

    const int SZEROKOSC_EKRANU = 800;
    const int WYSOKOSC_EKRANU = 600;

    int m_zniszczoneBloki = 0;
    Clock m_gameClock;

public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void resetGame();   
};
