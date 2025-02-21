#ifndef PLATFORM_MANAGER_H
#define PLATFORM_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PlatformManager {
    public:
        PlatformManager() = default;
        bool loadPlatformsFromFile(const std::string& filename);
        const std::vector<sf::RectangleShape>& getPlatforms() const;

    private:
        std::vector<sf::RectangleShape> platforms;
        void createPlatform(float x, float y, float width, float height);
};

#endif