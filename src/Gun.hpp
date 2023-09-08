#pragma once
#include "Gamew.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>

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

    Gun(Types type, Gamew &gamew);
    ~Gun();
    sf::Sprite &GetSprite();
    void Shoot(sf::Vector2f pos, Entity *ptrSelf);
    Types GetType() { return type; };
    static sf::Texture *GetTexture(Types type);

  private:
    friend Interface;

    static std::map<Types, std::shared_ptr<sf::Texture>> mapTextures;
    static bool initTextures;

    int distAnimShoot;
    int ammo = 999;
    Gamew &gamew;
    Animation *shoot;
    sf::Sprite sprite;
    Types type;
};
