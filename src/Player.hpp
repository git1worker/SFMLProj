#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"


class Player : public Entity {
public:

    enum Types {
        armoredAgent,
        greenAgent
    };

    Player(sf::RenderWindow *window, Types type, sf::Vector2f spawn);
    
    void Draw() override;
    void Update() override;

private:
    std::string name;
    sf::RenderWindow* window;
    sf::Sprite body, hand;
    sf::Texture textureBody;
    Types type;
    sf::Vector2f spawn;
    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;
    bool flipped = false;
};