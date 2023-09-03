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

    // The physical model for interacting with other entities and tiles.
    // This is mean that entity possesses coordinates relative the center of axes (coords 0, 0)
    // It does not include offsetRelativeCenter because offset should affect relative the main player
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