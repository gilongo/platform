#include <SFML/Graphics.hpp>
#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Unicredit");
    window.setFramerateLimit(60);

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(window.getSize().x - 100.0f, 50.0f));
    floor.setFillColor(sf::Color::Green);
    floor.setPosition(sf::Vector2f(0, window.getSize().y - floor.getSize().y));

    Player player(window.getSize(), floor);

    while (window.isOpen()) {
        while(auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.update();

        if (player.isDead()) {
            window.clear(sf::Color::Red);
        } else {
            window.clear(sf::Color::Cyan);
        }

        window.draw(floor);
        window.draw(player.getShape());
        window.display();
    }

    return 0;
}