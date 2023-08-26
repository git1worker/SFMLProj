#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"


class Player : public Entity {
public:
    enum Types {
        armoredAgent,
        greenAgent
    };


    Player(sf::RenderWindow *window, Types type);
    
    void Draw() override;
    void Update() override;


private:
    std::string name;
    sf::RenderWindow* window;
    sf::Sprite body, hand;
    
};