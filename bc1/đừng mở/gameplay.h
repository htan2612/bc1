#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

const int BOARD_SIZE = 12;

struct Cell {
    int c; // 0 = trống, -1 = X, 1 = O
    sf::RectangleShape shape;
};

class Gameplay {
private:
    std::vector<std::vector<Cell>> board;
    bool turn; // true = X, false = O
    bool gameOver;
    std::string winner;
    std::string playerX;
    std::string playerO;
    int cursorRow, cursorCol;
    sf::RectangleShape cursor;
    float CELL_SIZE;
    float offsetX, offsetY;

public:
    Gameplay();
    void reset();
    void handleInput(sf::Keyboard::Scancode key, bool soundOn, sf::Sound& sfx);
    void render(sf::RenderWindow& window, const sf::Font& font, float width, float height);
    bool checkWin(int i, int j);
    bool saveGame(const char* filename);
    bool loadGame(const char* filename);
    bool isGameOver() const { return gameOver; }
};

#endif