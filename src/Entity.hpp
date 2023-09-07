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
    virtual void Hit(float posX, float posY, sf::Vector2f direction) { HP -= 25; }
    bool DeleteIt() { return deleteIt; }

    // The physical model for interacting with other entities and tiles.
    // This is mean that entity possesses coordinates relative the center of axes (coords 0, 0)
    // It does not include offsetRelativeCenter because offset should affect relative the main player
    sf::FloatRect posRect{};

    // Velocity of moving
    float velocity = 3.5;

protected:

    bool flipped = false;
    Types type;
    bool deleteIt = false;
    int HP = 100;
    int cntFreeFall;
    // Vector of velocity relative X - right and Y - down
    sf::Vector2f direction{};
    
};