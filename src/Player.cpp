#include "Player.h"

Player::Player() {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(400.0f, 300.0f));
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.move(sf::Vector2(-speed, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.move(sf::Vector2(speed, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        shape.move(sf::Vector2(0.0f, -speed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        shape.move(sf::Vector2(0.0f, speed));
    }
}

sf::RectangleShape& Player::getShape() {
    return shape;
}