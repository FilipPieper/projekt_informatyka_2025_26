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
