#include "Game.h"
#include <iostream>
#include <algorithm>  

static const char* FONT_PATH =
"C:/Users/admin/source/repos/SFML_2_5_1_test/SFML_2_5_1_test/font/arial.ttf";

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Paletka i pilka")
    , m_paletka(400, 550, 100, 20, 6)
    , m_pilka(400, 300, 4, 4, 10)
    , m_menu(800.f, 600.f)          
    , m_state(State::MenuState)     
{
    m_window.setFramerateLimit(60);
    resetGame(); // przygotuj planszê
}

void Game::resetGame()
{
    // Reset pozycji pi³ki i prêdkoœci
    m_pilka = Pilka(400, 300, 4, 4, 10);
    // Reset paletki
    m_paletka = Paddle(400, 550, 100, 20, 6);

    // Reset licznika zniszczonych bloków
    m_zniszczoneBloki = 0;

    // Reset zegara gry
    m_gameClock.restart();

    // Inicjalizacja bloków 
    m_bricks.buildLevel((float)SZEROKOSC_EKRANU);

}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update(m_deltaClock.restart());
        render();

        if (m_state == State::ExitState)
            m_window.close();
    }
}



void Game::update(sf::Time deltaTime)
{
    if (m_state == State::MenuState)
    {
        m_menu.update();
        return;
    }

    if (m_state != State::PlayingState)
        return;
    m_paletka.handleInput((float)SZEROKOSC_EKRANU);


    // --- SPRAWDZENIE PRZEGRANEJ ---
    if (m_pilka.getVx() == 0 && m_pilka.getVy() == 0)
    {
        std::cout << "Koniec gry! PRZEGRALES ! Ilosc zniszczonych blokow: " << m_zniszczoneBloki << "\n";
        float czas = m_gameClock.getElapsedTime().asSeconds();
        // Zapisujemy wynik: ile bloków zniszczono i czas gry
        Scoreboard::addScore(m_zniszczoneBloki, czas);

        // Powrót do menu
        m_state = State::MenuState;
        return;
    }

    // --- SPRAWDZENIE WYGRANEJ ---
    if (m_bricks.empty())
    {
        std::cout << "Brawo! Plansza wyczyszczona! Tworze nowa... Powodzenia \n";
        // tworzymy nowy poziom
        resetGame();
    }
    // ruch pi³ki
	m_pilka.update((float)SZEROKOSC_EKRANU, (float)WYSOKOSC_EKRANU, m_paletka);
    m_bricks.collide(m_pilka, m_zniszczoneBloki);
}

void Game::render()
{
    m_window.clear(Color::Magenta);

    // ======== MENU ========
    if (m_state == State::MenuState)
    {
        m_menu.draw(m_window);
    }

    // ======== WYNIKI ========
    else if (m_state == State::ScoresState)
    {
        sf::Font font;
        font.loadFromFile(FONT_PATH);

        Scoreboard::draw(m_window, font);
    }

    // ======== GRA ========
    else if (m_state == State::PlayingState)
    {
        m_window.draw(m_pilka.getShape());
        m_window.draw(m_paletka.getShape());
        m_bricks.draw(m_window);

    }

    m_window.display();
}
