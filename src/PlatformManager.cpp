#include "PlatformManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool PlatformManager::loadPlatformsFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y, width, height;

        if(!(iss >> x >> y >> width >> height)) {
            std::cerr << "Wrong line format: " << line << std::endl;
            continue;
        }

        createPlatform(x, y, width, height);
    }

    file.close();
    return true;
}

void PlatformManager::createPlatform(float x, float y, float width, float height) {
    sf::RectangleShape platform;
    platform.setSize(sf::Vector2f(width, height));
    platform.setFillColor(sf::Color::Green);
    platform.setPosition(sf::Vector2f(x, y));
    platforms.push_back(platform);
}

const std::vector<sf::RectangleShape>& PlatformManager::getPlatforms() const {
    return platforms;
}