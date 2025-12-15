#include "Bricks.h"
#include "Ball.h"
#include <algorithm>

void Bricks::buildLevel(float screenWidth)
{
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 4;
    const float ODSTEP = 2.f;
    const float WYS_BLOKU = 20.f;

    float szer =
        (screenWidth - (ILOSC_KOLUMN - 1) * ODSTEP) / ILOSC_KOLUMN;

    m_bricks.clear();

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {

            float posX = x * (szer + ODSTEP);
            float posY = y * (WYS_BLOKU + ODSTEP) + 60.f;

            int hp = 1;
            if (y == 0) hp = 3;
            else if (y <= 2) hp = 2;

            m_bricks.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(szer, WYS_BLOKU),
                hp
            );
        }
    }
}

void Bricks::collide(Pilka& ball, int& destroyedCounter)
{
    for (auto& b : m_bricks)
    {
        if (!b.czyZniszczony() &&
            ball.getShape().getGlobalBounds().intersects(b.getGlobalBounds()))
        {
            int hpPrzed = b.getHp();
            b.trafienie();

            if (hpPrzed > 0 && b.getHp() == 0)
                destroyedCounter++;

            ball.bounceY();
        }
    }

    m_bricks.erase(
        std::remove_if(m_bricks.begin(), m_bricks.end(),
            [](const Brick& b) { return b.czyZniszczony(); }),
        m_bricks.end()
    );
}

void Bricks::draw(sf::RenderWindow& window)
{
    for (auto& b : m_bricks)
        window.draw(b);
}

bool Bricks::empty() const
{
    return m_bricks.empty();
}

void Bricks::clear()
{
    m_bricks.clear();
}

std::vector<Brick>& Bricks::data() { return m_bricks; }
const std::vector<Brick>& Bricks::data() const { return m_bricks; }