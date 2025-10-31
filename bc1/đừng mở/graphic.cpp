#include "Graphic.h"
#include "Console.h"

bool Graphic::loadBackground(sf::Texture& texture, sf::Sprite& sprite, float width, float height) {
    if (!texture.loadFromFile("../assets/bg.png")) {
        Console::error("Không thể load ảnh background.jpg trong folder assets!");
        return false;
    }
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    float scaleX = width / texSize.x;
    float scaleY = height / texSize.y;
    sprite.setScale({ scaleX, scaleY });
    return true;
}

bool Graphic::loadFont(sf::Font& font) {
    if (!font.openFromFile("../assets/ARCADECLASSIC.TTF")) {
        Console::error("Không thể load font ARCADECLASSIC.TTF!");
        return false;
    }
    return true;
}