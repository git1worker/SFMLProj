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
    if (type == Types::AK) distAnimShoot = 41;
    else if (type == Types::Pistol) distAnimShoot = 31;
    sprite.setTexture(*mapTextures.at(type));
    sprite.setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
    shoot = new Animation(&gamew, "../assets/img/guns/shoot.png", 50, 15, false);
    shoot->sprite.setOrigin(sf::Vector2f(0, shoot->sprite.getTextureRect().height / 2));
}

Gun::~Gun() { delete shoot; }

sf::Sprite &Gun::GetSprite() { return sprite; }

void Gun::Shoot(sf::Vector2f pos, Entity *ptrSelf) {
    // std::cout << "---" << std::endl;
    int hyp = distAnimShoot;
    if (gamew.player->flipped) hyp = distAnimShoot + 13;
    double cos = sqrt(1 / (1 + gamew.player->tg * gamew.player->tg));
    double addX = cos * hyp;
    double addY = sqrt(hyp * hyp - addX * addX);
    
    if (gamew.player->flipped) {
        addX *= -1;
        if (gamew.player->tg < 0)
            addY *= -1;
    } else {
        if (gamew.player->tg > 0)
            addY *= -1;
    }
    addY -= 5;
    shoot->sprite.setPosition(sf::Vector2f(pos.x + gamew.offsetRelativeCenter.x + addX, pos.y + gamew.offsetRelativeCenter.y + addY + 3));
    shoot->sprite.setRotation(-(atan(gamew.player->tg) * 180 / 3.1415));
    if (gamew.player->flipped) shoot->SetFlipped();
    else shoot->SetOrigin();
    shoot->Start();
    gamew.BulletsVector.emplace_back(std::make_unique<Bullet>(&gamew, pos, ptrSelf));
    gamew.AnimsVector.push_back(shoot);
}
