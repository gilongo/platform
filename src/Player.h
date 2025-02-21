#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player(sf::Vector2u windowSize);
        void update(const std::vector<sf::RectangleShape>& platforms);
        sf::RectangleShape& getShape();
        bool isDead() const;

    private:
        sf::RectangleShape shape;
        sf::Vector2u windowSize;

        float speed = 5.0f;
        float gravity = 0.5f;
        float velocityY = 0.0f;
        float velocityX = 0.0f;
        float jumpStrength = -12.0f;
        bool isOnGround = false;
        bool dead = false;

        void handleHorizontalCollisions(const std::vector<sf::RectangleShape>& platforms);
        void handleVerticalCollisions(const std::vector<sf::RectangleShape>& platforms);
        void applyGravity();
        void jump();
        void checkDeath();
};

#endif