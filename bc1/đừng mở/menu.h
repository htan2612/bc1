#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class GameState {
    MENU,
    PLAYING,
    SETTINGS,
    ABOUT,
    LOADGAME
};

class Menu {
private:
    std::vector<std::string> menuItems;
    std::vector<sf::Text> texts;
    std::vector<sf::RectangleShape> boxes;
    int selected;
    sf::Text title;

public:
    Menu();
    void init(const sf::Font& font, float width, float height);
    void handleInput(sf::Keyboard::Scancode key);
    void render(sf::RenderWindow& window);
    std::string getSelectedItem() const;
    void updateHighlight();
};

#endif