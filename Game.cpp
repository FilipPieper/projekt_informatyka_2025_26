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

    // Inicjalizacja bloków TO MA BYÆ W INNEJ KLASIE !!!!!!!
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 4;
    float ROZMIAR_BLOKU_X =
        (SZEROKOSC_EKRANU - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;

    m_bloki.clear();

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int L = 0;

            if (y == 0) L = 3;
            if (y == 1 || y == 2) L = 2;
            if (y >= 3) L = 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
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

void Game::processEvents()
{
    Event e;
    while (m_window.pollEvent(e))
    {
        if (e.type == Event::Closed)
            m_window.close();



        // ================= MENU =================
        if (m_state == State::MenuState)
        {
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Up) {
                    sf::sleep(sf::milliseconds(200));
                    m_menu.przesunG();
                }
                if (e.key.code == Keyboard::Down) {
                    sf::sleep(sf::milliseconds(200));
                    m_menu.przesunD();
                }

                if (e.key.code == Keyboard::Enter)
                {
                    int sel = m_menu.getSelectedItem();

                    if (sel == 0) {                // Nowa gra
                        resetGame();
                        m_state = State::PlayingState;
                    }
                 
                    else if (sel == 1) {           // Ostatnie wyniki
                        m_state = State::ScoresState;
                    }

                    else if (sel == 2) {           // Wczytaj gre
                        GameState state;
                        if (state.loadFromFile("zapis.txt", m_paletka, m_pilka, m_bloki)) {
                            std::cout << "Zapis wczytany!\n";
                            m_state = State::PlayingState;
                        }
                        else {
                            std::cout << "Blad podczas wczytywania zapisu!\n";
                            // zostajemy w menu
                        }
                    }
                    else if (sel == 3) {           // Wyjscie
                        m_state = State::ExitState;
                    }
                }
            }
        }


        // ================= WYNIKI =================
        else if (m_state == State::ScoresState)
        {
            if (e.type == Event::KeyPressed &&
                e.key.code == Keyboard::Escape)
            {
                m_state = State::MenuState;
            }
        }

        // ================= GRA =================
       
        // zapisywanie pod f5
        if (e.type == sf::Event::KeyPressed &&
            e.key.code == sf::Keyboard::F5)
        {
            GameState state;
            state.capture(m_paletka, m_pilka, m_bloki);

            if (state.saveToFile("zapis.txt"))
                std::cout << "Gra zapisana!\n";
            else
                std::cout << "Blad podczas zapisu!\n";
        }



        else if (m_state == State::PlayingState)
        {
            if (e.type == Event::KeyPressed &&
                e.key.code == Keyboard::Escape)
            {
                m_state = State::MenuState;
            }
        }
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

    // sterowanie paletk¹
    if (Keyboard::isKeyPressed(Keyboard::Left))
        m_paletka.moveLeft();
    if (Keyboard::isKeyPressed(Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(SZEROKOSC_EKRANU);


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
    if (m_bloki.empty())
    {
        std::cout << "Brawo! Plansza wyczyszczona! Tworze nowa... Powodzenia \n";

        // tworzymy nowy poziom
        resetGame();
    }

    // ruch pi³ki
    m_pilka.move();
    m_pilka.stopAtBottom(600.f);
    m_pilka.collideWalls(800.f, 600.f);

    // kolizja pi³ki z paletk¹
    m_pilka.collidePaddle(m_paletka);

    // kolizja pi³ki z blokami
    for (auto& blk : m_bloki) {
        if (!blk.czyZniszczony() &&
            m_pilka.getShape().getGlobalBounds().intersects(blk.getGlobalBounds())) {

            int hpPrzed = blk.getHp();

            blk.trafienie();

            // jesli klocek wlasnie zostal zniszczony (hp spadlo do 0)
            if (hpPrzed > 0 && blk.getHp() == 0) {
                m_zniszczoneBloki++;
            }

            m_pilka.bounceY();
        }
    }


    // usuwanie zniszczonych bloków
    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Brick& blk) { return blk.czyZniszczony(); }),
        m_bloki.end()
    );



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

        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(28);
        t.setFillColor(sf::Color::White);

        // naglowek
        t.setString("Ostatnie wyniki:");
        t.setPosition(100.f, 50.f);
        m_window.draw(t);

        // wczytaj wyniki z pliku
        auto wyniki = Scoreboard::loadScores();

        float y = 120.f;
        int nr = 1;

        for (const auto& w : wyniki) {
            std::string linia =
                std::to_string(nr) + ". "
                "Zniszczone bloki: " + std::to_string(w.blocks) +
                "   Czas: " + std::to_string(static_cast<int>(w.time)) + " s";

            t.setString(linia);
            t.setPosition(100.f, y);
            m_window.draw(t);

            y += 40.f;
            nr++;
        }

        // informacja o powrocie
        t.setString("ESC aby wrocic do menu");
        t.setPosition(100.f, y + 40.f);
        m_window.draw(t);
    }

    // ======== GRA ========
    else if (m_state == State::PlayingState)
    {
        m_window.draw(m_pilka.getShape());
        m_window.draw(m_paletka.getShape());

        for (auto& blk : m_bloki) {
            m_window.draw(blk);
        }
    }

    m_window.display();
}
