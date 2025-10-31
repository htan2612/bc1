#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML/Graphics.hpp>

class Graphic {
public:
    static bool loadBackground(sf::Texture& texture, sf::Sprite& sprite, float width, float height);
    static bool loadFont(sf::Font& font);
};

#endif