#include "Player.h"

Player::Player(sf::Vector2u windowSize) : windowSize(windowSize) {
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Red);
    reset();
}

void Player::update(const std::vector<sf::RectangleShape>& platforms) {
    if (dead) {
        updateDeathTimer();
        return;
    }

    velocityX = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocityX = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocityX = speed;
    }

    shape.move(sf::Vector2f(velocityX, 0));
    handleHorizontalCollisions(platforms);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isOnGround) {
        jump();
    }

    applyGravity();
    handleVerticalCollisions(platforms);
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

void Player::handleHorizontalCollisions(const std::vector<sf::RectangleShape>& platforms) {
    sf::FloatRect playerBounds = shape.getGlobalBounds();

    for (const auto& platform: platforms) {
        sf::FloatRect platformBounds = platform.getGlobalBounds();

        if (checkCollision(playerBounds, platformBounds)) {
            if(velocityX > 0) {
                shape.setPosition(sf::Vector2f(platformBounds.position.x - playerBounds.size.x, playerBounds.position.y));
            }
            else if(velocityX < 0) {
                shape.setPosition(sf::Vector2f(platformBounds.position.x + platformBounds.size.x, playerBounds.position.y));
            }
        }
    }
}

void Player::handleVerticalCollisions(const std::vector<sf::RectangleShape>& platforms) {
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    isOnGround = false;

    for(const auto& platform: platforms) {
        sf::FloatRect platformBounds = platform.getGlobalBounds();

        if(checkCollision(playerBounds, platformBounds)) {
            if(velocityY > 0) {
                shape.setPosition(sf::Vector2f(playerBounds.position.x, platformBounds.position.y - playerBounds.size.y));
                velocityY = 0.0f;
                isOnGround = true;
            }
            else if (velocityY < 0) {
                shape.setPosition(sf::Vector2f(playerBounds.position.x, platformBounds.position.y + playerBounds.size.x));
                velocityY = 0.0f;
            }
        }
    }
}

void Player::checkDeath() {
    if (shape.getPosition().y > windowSize.y) {
        dead = true;
        deathTimer.restart();
    }
}

void Player::updateDeathTimer() {
    if(deathTimer.getElapsedTime().asSeconds() >= respawnDeplay) {
        reset();
    }
}

void Player::reset() {
    dead = false;
    velocityX = 0.0f;
    velocityY = 0.0f;
    shape.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y - 150.0f));
}

sf::RectangleShape& Player::getShape() {
    return shape;
}

bool Player::isDead() const {
    return dead;
}