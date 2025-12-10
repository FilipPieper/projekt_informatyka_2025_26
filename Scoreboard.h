#pragma once
#include <vector>

struct ScoreEntry {
    int blocks;     // ile zniszczonych blokow
    float time;     // czas gry w sekundach
};

class Scoreboard {
public:
    // dodaje nowy wynik do pliku, trzyma max 4 ostatnie
    static void addScore(int blocks, float time);

    // wczytuje wszystkie wyniki z pliku
    static std::vector<ScoreEntry> loadScores();
};
