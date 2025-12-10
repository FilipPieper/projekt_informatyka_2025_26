#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define MAX_LICZBA_POZIOMOW 4

class Menu
{
private:
    sf::Font font;
    std::vector<sf::Text> menu; // elementy menu
    int selectedItem = 0;

    // Dekoracyjne obracaj¹ce siê kwadraty
    std::vector<sf::RectangleShape> kwadraty;


public:
    Menu(float width, float height);
    

    void przesunG(); // w górê
    void przesunD(); // w dó³

    int getSelectedItem() const { return selectedItem; }

    void draw(sf::RenderWindow& window);

    // animacja
    void update();

};
