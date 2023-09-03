#include "Bullet.hpp"
#include "Gamew.hpp"

Bullet::Bullet(Gamew* gamew, sf::Vector2f pos) : gamew(gamew), pos(pos) {
    texture.setFillColor(sf::Color(121, 121, 121));
    texture.setOutlineColor(sf::Color(40, 40, 40, 200));
    texture.setOutlineThickness(1);
    texture.setPosition(pos);
    tg = gamew->player->tg;
    isFlipped = gamew->player->flipped;

}

void Bullet::Update() {
    
    pos
}

void Bullet::Draw() {
    gamew->window->draw(texture);
}

