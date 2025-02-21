#include <SFML/Graphics.hpp>
#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Unicredit");
    window.setFramerateLimit(60);

    Player player;

    while (window.isOpen()) {

        while(auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.update();

        window.clear(sf::Color::Cyan);
        window.draw(player.getShape());
        window.display();
    }

    return 0;
}