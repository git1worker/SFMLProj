#pragma once
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile() = default;
    Tile(const Tile &other) = default;
    ~Tile() = default;
    Tile& operator=(const Tile& other) = default;
    
    sf::Sprite sprite;
    int id;
    bool canCollide = false;
    sf::IntRect intRect;

};