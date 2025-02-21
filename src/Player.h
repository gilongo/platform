#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
    public:
        Player();
        void update();
        sf::RectangleShape& getShape();

    private:
        sf::RectangleShape shape;
        float speed = 5.0f;
};

#endif