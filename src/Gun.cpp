#include "Gun.hpp"
#include "Animation.hpp"
#include "Player.hpp"
#include <cmath>
#include <iostream>

std::map<Gun::Types, std::shared_ptr<sf::Texture>> Gun::mapTextures = {{Gun::Types::Pistol, std::make_shared<sf::Texture>()},
                                                                       {Gun::Types::AK, std::make_shared<sf::Texture>()}};

bool Gun::initTextures = false;

Gun::Gun(Types type, Gamew &gamew) : type(type), gamew(gamew) {

    if (!initTextures) {
        initTextures = true;
        mapTextures.at(Types::Pistol)->loadFromFile("../assets/img/guns/pistol.png");
        mapTextures.at(Types::AK)->loadFromFile("../assets/img/guns/ak-47.png");
    }
    sprite.setTexture(*mapTextures.at(type));
    sprite.setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
    shoot = new Animation(&gamew, "../assets/img/guns/shoot.png", 110, 15, false);
    shoot->sprite.setOrigin(sf::Vector2f(0, shoot->sprite.getTextureRect().height / 2));
}

Gun::~Gun() { delete shoot; }

sf::Sprite &Gun::GetSprite() { return sprite; }

void Gun::Shoot(sf::Vector2f pos, Entity *ptrSelf) {
    // std::cout << "---" << std::endl;
    shoot->sprite.setPosition(sf::Vector2f(pos.x + gamew.offsetRelativeCenter.x, pos.y + gamew.offsetRelativeCenter.y));
    shoot->sprite.setRotation(-(atan(gamew.player->tg) * 180 / 3.1415));
    shoot->Start();
    gamew.BulletsVector.emplace_back(std::make_unique<Bullet>(&gamew, pos, ptrSelf));
    gamew.AnimsVector.push_back(shoot);
}
