#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Unicredit");
    window.setFramerateLimit(60);

    std::vector<sf::RectangleShape> platforms;

    auto createPlatform = [&](float x, float y, float width, float height) {
        sf::RectangleShape platform;
        platform.setSize(sf::Vector2f(width, height));
        platform.setFillColor(sf::Color::Green);
        platform.setPosition(sf::Vector2f(x, y));
        platforms.push_back(platform);
    };

    createPlatform(0, 550, 200, 50);
    createPlatform(300, 550, 200, 50);
    createPlatform(600, 550, 200, 50);

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(window.getSize().x - 100.0f, 50.0f));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(sf::Vector2f(0, window.getSize().y - floor.getSize().y));

    Player player(window.getSize());

    while (window.isOpen()) {
        while(auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.update(platforms);

        window.clear(player.isDead() ? sf::Color::Red : sf::Color::Cyan);

        for (const auto& platform: platforms) {
            window.draw(platform);
        }

        window.draw(player.getShape());
        window.display();
    }

    return 0;
}