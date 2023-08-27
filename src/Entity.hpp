#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:

    Entity() = default;
    virtual ~Entity() = default;
    virtual void Draw() = 0;
    virtual void Update();
    bool DeleteIt() { return deleteIt; }
    
private:
    
    bool deleteIt = false;
    int x, y;
    int HP;
    int velocity;

};