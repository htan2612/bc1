#include "Menu.h"

Menu::Menu() : selected(0) {
    menuItems = { "New Game", "Load Game", "Settings", "ABOUT", "Exit" };
}

void Menu::init(const sf::Font& font, float width, float height) {
    texts.clear();
    boxes.clear();
    float startY = height / 2.f - (menuItems.size() * (height / 10.f)) / 2.f;
    float spacing = height / 9;

    for (size_t i = 0; i < menuItems.size(); ++i) {
        float posY = startY + i * spacing + 150;

        sf::Text text(font);
        text.setString(menuItems[i]);
        text.setCharacterSize(static_cast<unsigned int>(height / 20));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({ bounds.position.x + bounds.size.x / 2,
                        bounds.position.y + bounds.size.y / 2 });
        text.setFillColor(i == selected ? sf::Color::Cyan : sf::Color::White);
        text.setPosition({ width / 2, posY });
        texts.push_back(text);

        float boxWidth = width / 3;
        float boxHeight = height / 12;
        sf::RectangleShape box({ boxWidth, boxHeight });
        box.setOrigin({ boxWidth / 2, boxHeight / 2 });
        box.setPosition({ width / 2, posY });
        if (i == selected) {
            box.setFillColor(sf::Color({ 100, 100, 255, 180 }));
        }
        else {
            box.setFillColor(sf::Color({ 50, 80, 120, 140 }));
        }
        box.setOutlineThickness(3);
        box.setOutlineColor(sf::Color::White);
        boxes.push_back(box);
    }

    title.setFont(font);
    title.setString("CARO GAME");
    title.setCharacterSize(static_cast<unsigned int>(height / 10));
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin({ titleBounds.position.x + titleBounds.size.x / 2,
                     titleBounds.position.y + titleBounds.size.y / 2 });
    title.setPosition({ width / 2.f, height / 5.f });
    title.setFillColor(sf::Color::Yellow);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(6);
}

void Menu::handleInput(sf::Keyboard::Scancode key) {
    if (key == sf::Keyboard::Scancode::W) {
        selected = (selected - 1 + texts.size()) % texts.size();
        updateHighlight();
    }
    else if (key == sf::Keyboard::Scancode::S) {
        selected = (selected + 1) % texts.size();
        updateHighlight();
    }
}

void Menu::render(sf::RenderWindow& window) {
    window.draw(title);
    for (size_t i = 0; i < texts.size(); i++) {
        window.draw(boxes[i]);
        window.draw(texts[i]);
    }
}

std::string Menu::getSelectedItem() const {
    return menuItems[selected];
}

void Menu::updateHighlight() {
    for (size_t i = 0; i < texts.size(); i++) {
        bool isSelected = (i == selected);
        texts[i].setFillColor(isSelected ? sf::Color::Cyan : sf::Color::White);
        if (isSelected) {
            boxes[i].setFillColor(sf::Color(100, 180, 255, 200));
            boxes[i].setScale({ 1.1f, 1.1f });
        }
        else {
            boxes[i].setFillColor(sf::Color(50, 80, 120, 140));
            boxes[i].setScale({ 1.f, 1.f });
        }
    }
}