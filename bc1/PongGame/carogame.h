#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class CaroGame {
public:
    CaroGame(float winWidth, float winHeight, sf::Font& font, sf::Sound& placeSfx);
    void reset();
    void handleEvent(const sf::Event& event);
    void update(float deltaTime) {}
    void render(sf::RenderWindow& window);
    bool isRunning() const { return running; }

private:
    const int BOARD_SIZE = 12;
    const float CELL_SIZE = 48.f; // kích thước ô
    std::vector<std::vector<int>> board; // 0 = empty, -1 = X, 1 = O
    bool turn; // true = X (first), false = O
    bool running;
    sf::Vector2i cursor; // index (col,row)
    sf::Font& font;
    sf::Text statusText;
    sf::RectangleShape cellShape;
    float offsetX, offsetY;
    sf::Sound& sfxPlace;

    bool checkWin(int row, int col);
    bool inBoard(int r, int c) const { return r >= 0 && c >= 0 && r < BOARD_SIZE && c < BOARD_SIZE; }
};
