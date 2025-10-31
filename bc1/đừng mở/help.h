#ifndef HELP_H
#define HELP_H

#include <SFML/Graphics.hpp>

class Help {
public:
    static void renderInstructions(sf::RenderWindow& window, const sf::Font& font, float height);
};

#endif