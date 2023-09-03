#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class Gamew;

class Enemy : public Entity {
public:

    Enemy(Gamew &gamew, sf::Vector2f spawn);
    void Draw() override;
    void Update() override;
    ~Enemy();

private:

    void UpdateDirection();
    void CheckJump();
    void UpdatePosition();
    bool IsThisInsideWindow();

    Gamew &gamew;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;

};