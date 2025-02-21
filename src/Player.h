#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player(sf::Vector2u windowSize, sf::RectangleShape& floor);
        void update();
        sf::RectangleShape& getShape();
        bool isDead() const;

    private:
        sf::RectangleShape shape;
        sf::Vector2u windowSize;
        sf::RectangleShape& floor;

        float speed = 5.0f;
        float gravity = 0.5f;
        float velocityY = 0.0f;
        float jumpStrength = -12.0f;
        bool isOnGround = false;
        bool dead = false;

        void handleCollisions();
        void applyGravity();
        void jump();
        void checkDeath();
};

#endif