#include "Help.h"

void Help::renderInstructions(sf::RenderWindow& window, const sf::Font& font, float height) {
    sf::Text instructionText(font);
    instructionText.setString("WASD: Move | Enter: Place | L: Save | T: Load | ESC: Menu");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color(200, 200, 200));
    instructionText.setPosition({ 50, height - 40 });
    window.draw(instructionText);
}