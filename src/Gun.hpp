#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include "Gamew.hpp"

#define IDENTATION_AT_GUN_X 2
#define IDENTATION_AT_GUN_Y 7


class Gun {
public:
    enum Types {
        Pistol,
        AK,
    };

    Gun(Types type, Gamew& gamew);
    sf::Sprite& GetSprite();
    void Shoot();
    
    
private:
    static std::map<Types, std::shared_ptr<sf::Texture>> mapTextures;
    static bool initTextures;

    Gamew& gamew;
    sf::Sprite sprite;
    Types type;
};

