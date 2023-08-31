#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Animation.hpp"

class Gamew;

class Player : public Entity
{
public:
    

    Player(Gamew &gamew, Types type, sf::Vector2f spawn);
    ~Player();

    void Draw() override;
    void Update() override;
    void MoveStop();

private:
    // Return True if player are in free fall
    void HandleMovement();
    void CollideCheck();
    void MovePlayerUp();
    void MovePlayerLeft();
    void MovePlayerDown();
    void MovePlayerDown(const float px);
    void MovePlayerRight();
    void MovePlayerJump();
    void UpdateDirection();

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

};