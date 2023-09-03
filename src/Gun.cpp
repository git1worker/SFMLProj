#include "Gun.hpp"
#include <iostream>
#include "Player.hpp"

std::map<Gun::Types, std::shared_ptr<sf::Texture>> Gun::mapTextures = {
    {Gun::Types::Pistol, std::make_shared<sf::Texture>()},
    {Gun::Types::AK, std::make_shared<sf::Texture>()}
};

bool Gun::initTextures = false;

Gun::Gun(Types type, Gamew& gamew) : type(type), gamew(gamew) {

    if (!initTextures){
        initTextures = true;
        mapTextures.at(Types::Pistol)->loadFromFile("../assets/img/guns/pistol.png");
        mapTextures.at(Types::AK)->loadFromFile("../assets/img/guns/ak-47.png");
    }
    sprite.setTexture(*mapTextures.at(type));
    sprite.setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
}

sf::Sprite &Gun::GetSprite() {
    return sprite;
}

void Gun::Shoot() {
    //std::cout << gamew.player->tg << std::endl;
    gamew.BulletsVector.emplace_back(std::make_unique<Bullet>(&gamew, sprite.getPosition()));
}
