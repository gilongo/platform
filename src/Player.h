#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player(sf::Vector2u windowSize);
        void update();
        sf::RectangleShape& getShape();

    private:
        sf::RectangleShape shape;
        sf::Vector2u windowSize;

        float speed = 5.0f;
        float gravity = 0.5f;
        float velocityY = 0.0f;
        float jumpStrength = -12.0f;
        bool isOnGround = false;

        void handleWindowCollision();
        void applyGravity();
        void jump();
};

#endif