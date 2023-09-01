#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Animation.hpp"

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
    

    Player(Gamew &gamew, Types type, sf::Vector2f spawn);
    ~Player();

    void Draw() override;
    void Update() override;
    void MoveStop();

private:
    
    void CollideCheck();
    void CollideCheckV2();
    void MovePlayerJump();
    void UpdateDirection();
    float GetFreeFall();
    bool CheckFreeFall();

    Gamew &gamew;
    std::string name;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    
    sf::Vector2f spawn;
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;
    bool flipped = false;
    Animation *move;
    bool animated = false;
    float currSpeedFall = 2;
    bool isFalling = false;
};