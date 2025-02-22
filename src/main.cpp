#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlatformManager.h"
#include <iostream>

int main() {

    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Platform");
    window.setFramerateLimit(60);

    PlatformManager platformManager;
    if (!platformManager.loadPlatformsFromFile("../platforms.txt")) {
        std::cerr << "Errore nel caricamento delle piattaforme." << std::endl;
        return -1;
    }

    Player player(window.getSize());

    sf::View view(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight)));
    window.setView(view);

    float levelWidth = 1200.0f;

    while (window.isOpen()) {
        while(auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        player.update(platformManager.getPlatforms());

        sf::Vector2f playerPos = player.getShape().getPosition();
        float halfWindowWidth = windowWidth / 2.0f;

        float viewCenterX = playerPos.x;

        if (viewCenterX < halfWindowWidth) {
            viewCenterX = halfWindowWidth;
        } else if (viewCenterX > levelWidth - halfWindowWidth) {
            viewCenterX = levelWidth - halfWindowWidth;
        }

        view.setCenter(sf::Vector2f(viewCenterX, windowHeight / 2.0f));
        window.setView(view);

        window.clear(player.isDead() ? sf::Color::Red : sf::Color::Cyan);

        for (const auto& platform : platformManager.getPlatforms()) {
            window.draw(platform);
        }

        window.draw(player.getShape());
        window.display();
    }

    return 0;
}