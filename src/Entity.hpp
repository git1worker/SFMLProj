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

    // The physical model for interacting with the 
    // other entities and tiles.
    sf::FloatRect posRect{};

    // Velocity of moving
    float velocity = 3.5;

protected:

    Types type;
    bool deleteIt = false;
    int HP;
    int cntFreeFall;
    // Direction relative X - right and Y - down
    sf::Vector2f direction{};
    
};