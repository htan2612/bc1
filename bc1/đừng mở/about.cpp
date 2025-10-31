#include "About.h"

void About::render(sf::RenderWindow& window, const sf::Font& font, float width, float height) {
    sf::Text announce(font);
    announce.setString("COMING SOON");
    sf::FloatRect anBounds = announce.getLocalBounds();
    announce.setOrigin({ anBounds.size.x / 2, anBounds.size.y / 2 });
    announce.setPosition({ width / 2, height / 2 });
    announce.setCharacterSize(height / 10);
    announce.setFillColor(sf::Color::Red);
    window.draw(announce);
}