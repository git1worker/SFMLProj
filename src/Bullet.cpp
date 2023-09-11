#include "Bullet.hpp"
#include "Gamew.hpp"
#include "Player.hpp"
#include <cmath>
#include "Debug.hpp"

Bullet::Bullet(Gamew *gamew, sf::Vector2f pos, float tg, Entity *ptrSelf) : gamew(gamew), pos(pos), ptrSelf(ptrSelf) {
    texture.setFillColor(sf::Color(100, 100, 100));
    texture.setOutlineColor(sf::Color(200, 0, 0));
    texture.setSize(sf::Vector2f(3, 1));
    texture.setOutlineThickness(1);
    texture.setPosition(pos);
    texture.setRotation(-(atan(tg) * 180 / 3.1415));
    cos = sqrt(1 / (1 + tg * tg));
    sin = sqrt(1 - cos * cos);
    if (ptrSelf == gamew->player){
        direction.x = velocity * cos + (rand() % 4) - 2;
        direction.y = velocity * sin + (rand() % 4) - 2;
    } else {
        direction.x = velocity * cos + (rand() % 8) - 4;
        direction.y = velocity * sin + (rand() % 8) - 4;
    }
    
    if (ptrSelf->flipped) {
        direction.x *= -1;
        if (tg < 0)
            direction.y *= -1;
    } else {
        if (tg > 0)
            direction.y *= -1;
    }
    // std::cout << direction.x << ' ' << direction.y << std::endl;
}

void Bullet::Update() {
    bool flag = true;
    
    for (int i = 1; i < velocity; i += 10) {
        
        for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjVector.begin(); it != gamew->ObjVector.end() && flag; ++it) {
            if ((*it)->isMovable() && (*it)->isCollidable()) {
                if ((*it)->collide(sf::FloatRect(pos.x + (direction.x / velocity) * i, pos.y + (direction.y / velocity) * i, texture.getSize().x,
                                                 texture.getSize().y)))
                    flag = false;
            }
        }
        
        if (ptrSelf == gamew->player){
            for (std::list<std::unique_ptr<Entity>>::iterator it = gamew->EntitiesVector.begin(); it != gamew->EntitiesVector.end() && flag; ++it)
                if ((*it)->posRect.contains(pos.x + (direction.x / velocity) * i, pos.y + (direction.y / velocity) * i) && (*it).get() != ptrSelf) {
                    flag = false;
                    (*it)->Hit(pos.x + (direction.x / velocity) * i, pos.y + (direction.y / velocity) * i, direction);
                }
        }
        else {
            if (gamew->player->posRect.contains(pos.x + (direction.x / velocity) * i, pos.y + (direction.y / velocity) * i)) {
                flag = false;
                gamew->player->Hit(pos.x + (direction.x / velocity) * i, pos.y + (direction.y / velocity) * i, direction);
            }
        }
        
    }
    if (!flag || ++cnt > 1000 / velocity)
        deleteIt = true;
    else
        pos += direction;
    
}

void Bullet::Draw() {
    texture.setPosition(pos.x + gamew->offsetRelativeCenter.x, pos.y + gamew->offsetRelativeCenter.y);
    gamew->window->draw(texture);
}
