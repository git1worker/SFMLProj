#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include "Gamew.hpp"

#define IDENTATION_AT_GUN_X 2
#define IDENTATION_AT_GUN_Y 7

class Entity;
class Animation;

class Gun {
public:
    enum Types {
        Pistol,
        AK,
    };

    Gun(Types type, Gamew& gamew);
    ~Gun();
    sf::Sprite& GetSprite();
    void Shoot(sf::Vector2f pos, Entity* ptrSelf);
    
    
private:
    static std::map<Types, std::shared_ptr<sf::Texture>> mapTextures;
    static bool initTextures;

    Gamew& gamew;
    Animation* shoot;
    sf::Sprite sprite;
    Types type;
};

