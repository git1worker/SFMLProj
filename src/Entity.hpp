#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    Entity() = default;
    virtual ~Entity() = default;
    virtual void Draw() = 0;
    virtual void Update(){};
    bool DeleteIt() { return deleteIt; }

    sf::IntRect posRect{};
    float velocity = 2.5;

protected:
    bool deleteIt = false;
    int HP;
};