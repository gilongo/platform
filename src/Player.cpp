#include "Player.h"

Player::Player(sf::Vector2u windowSize, sf::RectangleShape& floor) : windowSize(windowSize), floor(floor) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Vector2f(windowSize.x / 2.0f, floor.getPosition().y - shape.getSize().y));
}

void Player::update() {
    if (dead) return;

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
    handleCollisions();
    checkDeath();
}

void Player::applyGravity() {
    velocityY += gravity;
    shape.move(sf::Vector2f(0, velocityY));
} 

void Player::jump() {
    velocityY = jumpStrength;
    isOnGround = false;
}

bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    auto rect1Position = sf::Vector2f(rect1.position);
    auto rect1Size = sf::Vector2f(rect1.size);

    auto rect2Position = sf::Vector2f(rect2.position);
    auto rect2Size = sf::Vector2f(rect2.size);

    return (
        rect1Position.x < rect2Position.x + rect2Size.x &&
        rect1Position.x + rect1Size.x > rect2Position.x &&
        rect1Position.y < rect2Position.y + rect2Size.y &&
        rect1Position.y + rect1Size.y > rect2Position.y
    );
}

void Player::handleCollisions() {
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    sf::FloatRect floorBounds = floor.getGlobalBounds();

    sf::Vector2f position = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    if (checkCollision(playerBounds, floorBounds) && velocityY >= 0) {
        shape.setPosition(sf::Vector2f(playerBounds.position.x, floorBounds.position.y - playerBounds.size.y));
        velocityY = 0.0f;
        isOnGround = true;
    }

    if (position.x < 0) {
        shape.setPosition(sf::Vector2f(0, position.y));
    }
    if (position.x + size.x > windowSize.x) {
        shape.setPosition(sf::Vector2f(windowSize.x - size.x, position.y));
    }
}

void Player::checkDeath() {
    if (shape.getPosition().y > windowSize.y) {
        dead = true;
    }
}

sf::RectangleShape& Player::getShape() {
    return shape;
}

bool Player::isDead() const {
    return dead;
}