#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "AnimHuman.hpp"
#include "Gun.hpp"

class Gamew;

class Enemy : public Entity {
public:

    Enemy(Gamew &gamew, sf::Vector2f spawn);
    void Draw() override;
    void Update() override;
    ~Enemy();

private:

    void UpdateDirection();
    void UpdatePosition();
    bool IsThisInsideWindow();
    float GetFreeFall();
    bool CheckFreeFall();
    void CollideCheck();
    void UpdateRotation();

    Gamew &gamew;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;

    AnimHuman *move;
    bool animated = false;
    float currSpeedFall = 2;
    bool isFalling = false;
    Gun gun{Gun::Types::Pistol, gamew};
};