#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>
#include "Animation.hpp"

#define IDENTATION_AT_GUN_X 2
#define IDENTATION_AT_GUN_Y 7

class Entity;
class Interface;
class Enemy;
class Gamew;

class Gun {
  public:
    enum Types {
        Pistol,
        AK,
    };

    Gun(Types type, Gamew *gamew);
    sf::Sprite &GetSprite();
    void Shoot(sf::Vector2f pos, float tg, Entity *ptrSelf);
    Types GetType() { return type; };
    void ChangeType(Types type);
    static sf::Texture *GetTexture(Types type);

  private:
    friend Interface;
    friend Entity;
    friend Enemy;

    static std::map<Types, std::shared_ptr<sf::Texture>> mapTextures;
    static bool initTextures;

    int distAnimShoot;
    int ammo = 999;
    Gamew *gamew;
    Animation shoot;
    sf::Sprite sprite;
    Types type;
};
