#include "Gameplay.h"
#include <fstream>

Gameplay::Gameplay()
    : board(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE)),
    turn(true),
    gameOver(false),
    playerX("Player X"),
    playerO("Player O"),
    cursorRow(0),
    cursorCol(0),
    CELL_SIZE(50.f),
    offsetX(0),
    offsetY(0) {
    cursor.setSize({ CELL_SIZE - 4.f, CELL_SIZE - 4.f });
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(3);
    cursor.setOutlineColor(sf::Color::Yellow);
}

void Gameplay::reset() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].c = 0;
            board[i][j].shape.setSize({ CELL_SIZE - 2.f, CELL_SIZE - 2.f });
            board[i][j].shape.setPosition({ offsetX + j * CELL_SIZE, offsetY + i * CELL_SIZE });
            board[i][j].shape.setFillColor(sf::Color(240, 240, 240, 50));
            board[i][j].shape.setOutlineThickness(1);
            board[i][j].shape.setOutlineColor(sf::Color(100, 100, 100));
        }
    }
    cursorRow = 0;
    cursorCol = 0;
    turn = true;
    gameOver = false;
    winner = "";
}

void Gameplay::handleInput(sf::Keyboard::Scancode key, bool soundOn, sf::Sound& sfx) {
    if (gameOver) return;

    if (key == sf::Keyboard::Scancode::W) {
        if (cursorRow > 0) cursorRow--;
    }
    else if (key == sf::Keyboard::Scancode::S) {
        if (cursorRow < BOARD_SIZE - 1) cursorRow++;
    }
    else if (key == sf::Keyboard::Scancode::A) {
        if (cursorCol > 0) cursorCol--;
    }
    else if (key == sf::Keyboard::Scancode::D) {
        if (cursorCol < BOARD_SIZE - 1) cursorCol++;
    }
    else if (key == sf::Keyboard::Scancode::Enter) {
        if (board[cursorRow][cursorCol].c == 0) {
            board[cursorRow][cursorCol].c = (turn ? -1 : 1);

            if (soundOn) sfx.play();

            if (checkWin(cursorRow, cursorCol)) {
                gameOver = true;
                winner = (turn ? playerX + " wins!" : playerO + " wins!");
            }

            turn = !turn;
        }
    }
    else if (key == sf::Keyboard::Scancode::L) {
        saveGame("save.caro");
    }
    else if (key == sf::Keyboard::Scancode::T) {
        loadGame("save.caro");
    }
}

void Gameplay::render(sf::RenderWindow& window, const sf::Font& font, float width, float height) {
    // Tính toán offset để căn giữa
    float boardWidth = BOARD_SIZE * CELL_SIZE;
    float boardHeight = BOARD_SIZE * CELL_SIZE;
    offsetX = (width - boardWidth) / 2;
    offsetY = (height - boardHeight) / 2;

    // Vẽ bàn cờ
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].shape.setPosition({ offsetX + j * CELL_SIZE, offsetY + i * CELL_SIZE });
            window.draw(board[i][j].shape);

            if (board[i][j].c == -1) {
                sf::Text mark(font);
                mark.setString("X");
                mark.setCharacterSize(static_cast<unsigned int>(CELL_SIZE - 15));
                mark.setFillColor(sf::Color::Red);
                sf::FloatRect bounds = mark.getLocalBounds();
                mark.setOrigin({ bounds.position.x + bounds.size.x / 2,
                               bounds.position.y + bounds.size.y / 2 });
                mark.setPosition({ offsetX + j * CELL_SIZE + CELL_SIZE / 2,
                                 offsetY + i * CELL_SIZE + CELL_SIZE / 2 });
                window.draw(mark);
            }
            else if (board[i][j].c == 1) {
                sf::Text mark(font);
                mark.setString("O");
                mark.setCharacterSize(static_cast<unsigned int>(CELL_SIZE - 15));
                mark.setFillColor(sf::Color::Blue);
                sf::FloatRect bounds = mark.getLocalBounds();
                mark.setOrigin({ bounds.position.x + bounds.size.x / 2,
                               bounds.position.y + bounds.size.y / 2 });
                mark.setPosition({ offsetX + j * CELL_SIZE + CELL_SIZE / 2,
                                 offsetY + i * CELL_SIZE + CELL_SIZE / 2 });
                window.draw(mark);
            }
        }
    }

    // Vẽ cursor
    if (!gameOver) {
        cursor.setPosition({ offsetX + cursorCol * CELL_SIZE, offsetY + cursorRow * CELL_SIZE });
        window.draw(cursor);
    }

    // Hiển thị lượt chơi hoặc kết quả
    if (gameOver) {
        sf::Text resultText(font);
        resultText.setString(winner);
        resultText.setCharacterSize(50);
        resultText.setFillColor(sf::Color::Green);
        sf::FloatRect resBounds = resultText.getLocalBounds();
        resultText.setOrigin({ resBounds.position.x + resBounds.size.x / 2,
                              resBounds.position.y + resBounds.size.y / 2 });
        resultText.setPosition({ width / 2, 50 });
        window.draw(resultText);
    }
    else {
        sf::Text turnText(font);
        turnText.setString(turn ? (playerX + "'s turn (X)") : (playerO + "'s turn (O)"));
        turnText.setCharacterSize(30);
        turnText.setFillColor(sf::Color::White);
        turnText.setPosition({ 50, 50 });
        window.draw(turnText);
    }

    // Hướng dẫn
    sf::Text instructionText(font);
    instructionText.setString("WASD: Move | Enter: Place | L: Save | T: Load | ESC: Menu");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color(200, 200, 200));
    instructionText.setPosition({ 50, height - 40 });
    window.draw(instructionText);
}

bool Gameplay::checkWin(int i, int j) {
    int c = board[i][j].c;
    if (c == 0) return false;

    int dx[] = { 0, 1, 1, 1 };
    int dy[] = { 1, 0, 1, -1 };

    for (int dir = 0; dir < 4; ++dir) {
        int count = 1;

        for (int k = 1; k < 5; ++k) {
            int ni = i + dx[dir] * k;
            int nj = j + dy[dir] * k;
            if (ni < 0 || nj < 0 || ni >= BOARD_SIZE || nj >= BOARD_SIZE) break;
            if (board[ni][nj].c == c) count++;
            else break;
        }

        for (int k = 1; k < 5; ++k) {
            int ni = i - dx[dir] * k;
            int nj = j - dy[dir] * k;
            if (ni < 0 || nj < 0 || ni >= BOARD_SIZE || nj >= BOARD_SIZE) break;
            if (board[ni][nj].c == c) count++;
            else break;
        }

        if (count >= 5) return true;
    }
    return false;
}

bool Gameplay::saveGame(const char* filename) {
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            f.write((char*)&board[i][j].c, sizeof(int));
    f.write((char*)&turn, sizeof(bool));
    f.close();
    return true;
}

bool Gameplay::loadGame(const char* filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f) return false;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            f.read((char*)&board[i][j].c, sizeof(int));
    f.read((char*)&turn, sizeof(bool));
    f.close();
    gameOver = false;
    winner = "";
    return true;
}