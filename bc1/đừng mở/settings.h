#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Settings {
private:
    bool soundOn;

public:
    Settings();
    void toggle(sf::Music& music);
    void render(sf::RenderWindow& window, const sf::Font& font, float width, float height);
    bool isSoundOn() const { return soundOn; }
};

#endif