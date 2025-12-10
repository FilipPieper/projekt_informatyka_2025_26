#include "Menu.h"
#include <iostream>

static const char* FONT_PATH = "C:/Users/admin/source/repos/SFML_2_5_1_test/SFML_2_5_1_test/font/arial.ttf";

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile(FONT_PATH))
    {
        std::cout << "BLAD: nie moge zaladowac arial.ttf\n";
        return;
    }

    menu.resize(MAX_LICZBA_POZIOMOW);

    // --- Nowa gra
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 1.f);

    // --- Ostatnie wyniki
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Ostatnie wyniki");
    menu[1].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 2.f);
    // --- Wczytaj Gre
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wczytaj gre");
	menu[2].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 3.f);
    // --- Wyjscie
    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Wyjscie");
    menu[3].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1.f) * 4.f);
    

    //kwadraciki
    kwadraty.clear();

    auto makeSquare = [](sf::Vector2f pos) {
        sf::RectangleShape sq;

        // rozmiar kwadratu
        sq.setSize(sf::Vector2f(40.f, 40.f));

        // origin w œrodku -> obrót wokó³ w³asnej osi
        sq.setOrigin(20.f, 20.f);

        sq.setFillColor(sf::Color::Yellow);
        sq.setPosition(pos);

        return sq;
        };

    // kilka kwadratów w rogach menu
    kwadraty.push_back(makeSquare(sf::Vector2f(width * 0.2f, height * 0.3f)));
    kwadraty.push_back(makeSquare(sf::Vector2f(width * 0.8f, height * 0.3f)));
    kwadraty.push_back(makeSquare(sf::Vector2f(width * 0.2f, height * 0.7f)));
    kwadraty.push_back(makeSquare(sf::Vector2f(width * 0.8f, height * 0.7f)));
}



void Menu::draw(sf::RenderWindow& window)
{
    for (const auto& sq : kwadraty)
        window.draw(sq);

    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        window.draw(menu[i]);
}

void Menu::przesunG()
{
    // zdejmij podœwietlenie z aktualnego
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem--;
    if (selectedItem < 0)
        selectedItem = MAX_LICZBA_POZIOMOW - 1;

    // podœwietl nowy
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD()
{
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);

    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW)
        selectedItem = 0;

    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::update()
{
    // obracamy ka¿dy kwadrat trochê w ka¿dej klatce
    for (auto& sq : kwadraty)
    {
        sq.rotate(1.0f); // 1 stopieñ na klatkê
    }
}
