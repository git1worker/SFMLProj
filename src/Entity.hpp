#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:

    Entity() = default;
    
    virtual void Draw() = 0;
    virtual void Update();
    
private:
    int x, y;
    int HP;
    int velocity;

};