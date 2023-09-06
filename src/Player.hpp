#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "AnimHuman.hpp"
#include "Gun.hpp"

class Gamew;

class Player : public Entity
{
// Physical model for all players are with the rect below
// posRect: l = 0 cords at sprite + 3 px
//          t = 0 cords at sprite + 4 px 
//          w = w at sprite - 3 * 2
//          h = h at sprite - t
// 
public:
    friend Gun;
    friend Bullet;

    Player(Gamew &gamew, Types type, sf::Vector2f spawn);
    ~Player();
    void Shoot();
    void Draw() override;
    void Update() override;
    void MoveStop();

private:


    
    void CollideCheck();
    void StartJump();
    void CheckJump();
    void UpdateDirection();
    float GetFreeFall();
    bool CheckFreeFall();
    bool CheckCanMoveUp();
    void UpdateRotation();

    Gamew &gamew;
    std::string name;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    
    sf::Vector2f spawn;
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;
    AnimHuman *move;
    bool animated = false;
    float currSpeedFall = 2;
    bool isFalling = false;
    bool jumping = false;
    float energyJump = 0;
    double tg, sin;
    Gun gun{Gun::Types::AK, gamew};
};