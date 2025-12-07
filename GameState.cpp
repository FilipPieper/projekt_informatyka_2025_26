#include "GameState.h"

void GameState::capture(const Paddle& paletka, const Pilka& pilka, const std::vector<Brick>& bloki) {
	//Paletka
	paddlePosition = sf::Vector2f(paletka.getX(), paletka.getY());
	//Pi³ka
	ballPosition = sf::Vector2f(pilka.getX(), pilka.getY());
	ballVelocity = sf::Vector2f(pilka.getVx(), pilka.getVy());
	//Bloki
	blocks.clear();
	for (const auto& blok : bloki) {
		BlockData data;
		data.x = blok.getPosition().x;
		data.y = blok.getPosition().y;
		data.hp = blok.getHp();
		blocks.push_back(data);
	}
}

bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Zapis pozycji paletki
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Zapis pozycji i prêdkoœci pi³ki
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";

    // Zapis liczby bloków
    file << "BLOCKS " << blocks.size() << "\n";

    // Zapis danych bloków
    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}



bool GameState::loadFromFile(const std::string& filename,
    Paddle& paletka, Pilka& pilka,
    std::vector<Brick>& bloki)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string tag;

    // ===== PADDLE =====
    if (!(file >> tag) || tag != "PADDLE")
        return false;

    float px, py;
    if (!(file >> px >> py))
        return false;

    // ===== BALL =====
    if (!(file >> tag) || tag != "BALL")
        return false;

    float bx, by, vx, vy;
    if (!(file >> bx >> by >> vx >> vy))
        return false;

    // ===== BLOCKS =====
    if (!(file >> tag) || tag != "BLOCKS")
        return false;

    int count;
    if (!(file >> count))
        return false;

    // odtworzenie elementow
    paletka = Paddle(px, py, 100.f, 20.f, 6.f);
    pilka = Pilka(bx, by, vx, vy, 10.f);

    bloki.clear();

    const int ILOSC_KOLUMN = 8;
    const float SZEROKOSC_EKRANU = 800.f;
    float ROZMIAR_BLOKU_X =
        (SZEROKOSC_EKRANU - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 20.f;

    for (int i = 0; i < count; ++i) {
        float x, y;
        int hp;
        if (!(file >> x >> y >> hp))
            return false;

        if (hp > 0) {
            bloki.emplace_back(
                sf::Vector2f(x, y),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                hp
            );
        }
    }

    return true;
}




