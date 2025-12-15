#include "Scoreboard.h"
#include <fstream>
#include <algorithm>

static const char* SCORE_FILE = "wyniki.txt";

std::vector<ScoreEntry> Scoreboard::loadScores()
{
    std::vector<ScoreEntry> scores;

    std::ifstream file(SCORE_FILE);
    if (!file.is_open())
        return scores;

    ScoreEntry e;
    while (file >> e.blocks >> e.time) {
        scores.push_back(e);
    }

    return scores;
}

void Scoreboard::addScore(int blocks, float time)
{
    // wczytaj dotychczasowe wyniki
    auto scores = loadScores();

    // dodaj nowy wynik na koniec
    scores.push_back({ blocks, time });

    // jesli jest wiecej niz 4, usun najstarsze z przodu
    while (scores.size() > 4) {
        scores.erase(scores.begin());
    }

    // zapisz z powrotem do pliku
    std::ofstream file(SCORE_FILE);
    if (!file.is_open())
        return;

    for (const auto& s : scores) {
        file << s.blocks << " " << s.time << "\n";
    }
}

void Scoreboard::draw(sf::RenderWindow& window, const sf::Font& font)
{
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(28);
    t.setFillColor(sf::Color::White);

    // naglowek
    t.setString("Ostatnie wyniki:");
    t.setPosition(100.f, 50.f);
    window.draw(t);

    // wyniki
    auto wyniki = loadScores();
    float y = 120.f;
    int nr = 1;

    for (const auto& w : wyniki) {
        std::string linia =
            std::to_string(nr) + ". "
            "Zniszczone bloki: " + std::to_string(w.blocks) +
            "   Czas: " + std::to_string((int)w.time) + " s";

        t.setString(linia);
        t.setPosition(100.f, y);
        window.draw(t);

        y += 40.f;
        nr++;
    }

    // stopka
    t.setString("ESC aby wrocic do menu");
    t.setPosition(100.f, y + 40.f);
    window.draw(t);
}