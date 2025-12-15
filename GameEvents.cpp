#include "Game.h"

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
                        if (state.loadFromFile("zapis.txt", m_paletka, m_pilka, m_bricks)) {
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
            state.capture(m_paletka, m_pilka, m_bricks);

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