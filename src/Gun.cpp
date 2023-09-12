#include "Gun.hpp"
#include "Animation.hpp"
#include "Player.hpp"
#include <cmath>
#include <iostream>
#include "Gamew.hpp"
#include "Debug.hpp"

std::map<Gun::Types, std::shared_ptr<sf::Texture>> Gun::mapTextures = {{Gun::Types::Pistol, std::make_shared<sf::Texture>()},
                                                                       {Gun::Types::AK, std::make_shared<sf::Texture>()}};

bool Gun::initTextures = false;

Gun::Gun(Types type, Gamew *gamew) : type(type), gamew(gamew) {

    if (!initTextures) {
        initTextures = true;
        mapTextures.at(Types::Pistol)->loadFromFile("../assets/img/guns/pistol.png");
        mapTextures.at(Types::AK)->loadFromFile("../assets/img/guns/ak-47.png");
    }
    if (type == Types::AK)
        distAnimShoot = 41;
    else if (type == Types::Pistol)
        distAnimShoot = 31;
    sprite.setTexture(*mapTextures.at(type));
    sprite.setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
    //std::cout << "Gun() " << this << std::endl;
    
    shoot = Animation(gamew, "../assets/img/guns/shoot.png", 50, 15, false);
    //RTDrawing(gamew->window.get(), shoot.sprite);
    shoot.sprite.setOrigin(sf::Vector2f(0, shoot.sprite.getTextureRect().height / 2));
}

void Gun::ChangeType(Types type)
{
    this->type = type;
    if (type == Types::AK)
        distAnimShoot = 41;
    else if (type == Types::Pistol)
        distAnimShoot = 31;
    sprite.setTexture(*mapTextures.at(type));
}

sf::Sprite &Gun::GetSprite() { return sprite; }

void Gun::Shoot(sf::Vector2f pos, float tg, Entity *ptrSelf) {
    // std::cout << "---" << std::endl;
    if (ammo > 0) {
        --ammo;
        int hyp = distAnimShoot;
        if (ptrSelf->flipped)
            hyp = distAnimShoot + 13;
        double cos = sqrt(1 / (1 + tg * tg));
        double addX = cos * hyp;
        double addY = sqrt(hyp * hyp - addX * addX);
        if (ptrSelf->flipped) {
            addX *= -1;
            if (tg < 0)
                addY *= -1;
        } else {
            if (tg > 0)
                addY *= -1;
        }
        addY -= 5;
        shoot.setPosition(sf::Vector2f(pos.x + addX, pos.y + addY + 3));
        shoot.sprite.setRotation(-(atan(tg) * 180 / 3.1415));
        if (ptrSelf->flipped)
            shoot.SetFlipped();
        else
            shoot.SetOrigin();
        shoot.Start();
        gamew->BulletsList.emplace_back(std::make_unique<Bullet>(gamew, pos, tg, ptrSelf));
    }
}

sf::Texture *Gun::GetTexture(Types type) { return mapTextures.at(type).get(); }
