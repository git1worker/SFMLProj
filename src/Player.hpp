#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Animation.hpp"

class Gamew;

class Player : public Entity
{
public:
    enum Types
    {
        armoredAgent,
        greenAgent
    };

    Player(Gamew &gamew, Types type, sf::Vector2f spawn);
    ~Player();

    void Draw() override;
    void Update() override;
    void MoveStop();

private:
    // Return True if player are in free fall
    void HandleMovement();
    bool checkFreeFall();
    void MovePlayerUp();
    void MovePlayerLeft();
    void MovePlayerDown();
    void MovePlayerDown(const float px);
    void MovePlayerRight();
    void MovePlayerJump();

    Gamew &gamew;
    std::string name;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    Types type;
    sf::Vector2f spawn;
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;
    bool flipped = false;
    Animation *move;
    bool animated = false;
};