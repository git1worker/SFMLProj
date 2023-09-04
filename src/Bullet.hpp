#pragma once
#include <SFML/Graphics.hpp>

class Gamew;
class Entity;

class Bullet {
public:

    Bullet(Gamew* gamew, sf::Vector2f pos, Entity* ptrSelf);
    void Update();
    virtual void Draw();
    bool DeleteIt() { return deleteIt; }

private:
    
    Gamew* gamew;
    Entity* ptrSelf;
    sf::Vector2f pos, direction;
    double cos, sin;
    sf::RectangleShape texture;
    float velocity = 45;
    bool deleteIt = false;
    int cnt = 0;
};
