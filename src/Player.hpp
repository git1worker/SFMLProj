#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Gamew;

class Player : public Entity {
public:

    enum Types {
        armoredAgent,
        greenAgent
    };

    Player(Gamew& gamew, Types type, sf::Vector2f spawn);
    
    void Draw() override;
    void Update() override;
    void MovePlayerUp();
    void MovePlayerLeft();
    void MovePlayerDown();
    void MovePlayerRight();


private:



    Gamew& gamew;
    std::string name;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    Types type;
    sf::Vector2f spawn;
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;
    bool flipped = false;
    
};