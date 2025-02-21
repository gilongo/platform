#include "Player.h"

Player::Player(sf::Vector2u windowSize) : windowSize(windowSize) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y - shape.getSize().y));
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.move(sf::Vector2(-speed, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.move(sf::Vector2(speed, 0.0f));
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isOnGround) {
        jump();
    }

    applyGravity();
    handleWindowCollision();
}

void Player::applyGravity() {
    velocityY += gravity;
    shape.move(sf::Vector2f(0, velocityY));
} 

void Player::jump() {
    velocityY = jumpStrength;
    isOnGround = false;
}

void Player::handleWindowCollision() {
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    if (position.x < 0) {
        shape.setPosition(sf::Vector2f(0, position.y));
    }
    if (position.x + size.x > windowSize.x) {
        shape.setPosition(sf::Vector2f(windowSize.x - size.x, position.y));
    }

    if (position.y + size.y > windowSize.y) {
        shape.setPosition(sf::Vector2f(position.x, windowSize.y - size.y));
        velocityY = 0.0f;
        isOnGround = true;
    }

    if (position.y < 0) {
        shape.setPosition(sf::Vector2f(position.x, 0));
        velocityY = 0.0f;
    }
}

sf::RectangleShape& Player::getShape() {
    return shape;
}