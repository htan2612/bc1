#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <gl.h>

using namespace std;

namespace
{
    std::filesystem::path assetsDir()
    {
        return "assets"; // folder chứa ảnh background
    }
} // namespace

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.sRgbCapable = false;

    // Tạo cửa sổ SFML
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "SFML Background Only",
        sf::Style::Default,
        settings);

    window.setVerticalSyncEnabled(true);

    // Load ảnh background từ thư mục assets
    sf::Texture backgroundTexture(assetsDir() / "background.jpg");
    if (!backgroundTexture.getSize().x)
    {
        cerr << "Không thể load ảnh assets/background.jpg" << endl;
        return EXIT_FAILURE;
    }

    sf::Sprite background(backgroundTexture);

    // Căn chỉnh hình theo kích thước cửa sổ
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    background.setScale(scaleX, scaleY);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Escape))
            {
                window.close();
            }

            // Khi resize cửa sổ, scale lại ảnh nền
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::Vector2u newSize(resized->size.x, resized->size.y);
                float newScaleX = static_cast<float>(newSize.x) / textureSize.x;
                float newScaleY = static_cast<float>(newSize.y) / textureSize.y;
                background.setScale(newScaleX, newScaleY);
            }
        }

        // Xóa màn hình và vẽ lại background
        window.clear();
        window.draw(background);
        window.display();
    }

    return EXIT_SUCCESS;
}
