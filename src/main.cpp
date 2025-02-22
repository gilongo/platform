#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlatformManager.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Unicredit");
    window.setFramerateLimit(60);

    PlatformManager platformManager;
    if (!platformManager.loadPlatformsFromFile("../platforms.txt")) {
        std::cerr << "Errore nel caricamento delle piattaforme." << std::endl;
        return -1;
    }

    Player player(window.getSize());

    while (window.isOpen()) {
        while(auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.update(platformManager.getPlatforms());

        window.clear(player.isDead() ? sf::Color::Red : sf::Color::Cyan);

        for (const auto& platform : platformManager.getPlatforms()) {
            window.draw(platform);
        }

        window.draw(player.getShape());
        window.display();
    }

    return 0;
}