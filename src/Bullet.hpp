#pragma once
#include <SFML/Graphics.hpp>

class Gamew;

class Bullet {
public:

    Bullet(Gamew* gamew, sf::Vector2f pos);
    void Update();
    void Draw();


private:
    
    Gamew* gamew;
    sf::Vector2f pos;
    double tg;
    bool isFlipped;
    sf::RectangleShape texture;
    float velocity = 5;
};
