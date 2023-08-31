#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:

    enum Types
    {
        armoredAgent,
        greenAgent
    };

    Entity() = default;
    virtual ~Entity() = default;
    virtual void Draw() = 0;
    virtual void Update(){};
    bool DeleteIt() { return deleteIt; }

    sf::FloatRect posRect{};
    float velocity = 2.5;

protected:
    Types type;
    bool deleteIt = false;
    int HP;

    // Direction relative X - right and Y - down
    sf::Vector2f direction{};
    
};