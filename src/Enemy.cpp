#include "Enemy.hpp"
#include "Gamew.hpp"
#include "Player.hpp"
#include <cmath>
#include "Debug.hpp"
#include <iostream>

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2
#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)
#define IDENTATION_AT_POSRECT_LEFT 3
#define IDENTATION_AT_POSRECT_TOP 4

int Enemy::randCnt = 0;

Enemy::Enemy(Gamew *gamew, sf::Vector2f spawn) : gamew(gamew) {
    srand(time(NULL) + (++randCnt));
    type = Types::greenAgent;
    if (type == Types::armoredAgent) {
        textureBody.loadFromFile("../assets/img/characters/agent_2.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_gray.png");
        move = AnimHuman(gamew, "../assets/img/characters/anims_gray_agent.png", this);
    } else if (type == Types::greenAgent) {
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
        move = AnimHuman(gamew, "../assets/img/characters/anims_green_agent.png", this);
    }
    blood = SplashOfBlood(gamew);
    gun.ChangeType(static_cast<Gun::Types>(rand() % 2));
    body.setTexture(textureBody);
    posRect.left = spawn.x + IDENTATION_AT_POSRECT_LEFT;
    posRect.top = spawn.y + IDENTATION_AT_POSRECT_TOP;
    posRect.width = body.getTextureRect().width - IDENTATION_AT_POSRECT_LEFT * 2;
    posRect.height = body.getTextureRect().height - IDENTATION_AT_POSRECT_TOP;
    body.setPosition(sf::Vector2f(spawn.x - POINT_HAND_X + gamew->offsetRelativeCenter.x, spawn.y - POINT_HAND_Y + gamew->offsetRelativeCenter.y));
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    gun.GetSprite().setPosition(hand.getPosition());
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();

    hpShell.setOutlineColor(sf::Color::Black);
    hpShell.setOutlineThickness(1);
    hpShell.setFillColor(sf::Color(150, 150, 150, 100));
    hpShell.setSize(sf::Vector2f(bodyRect.width, 3));
    hpBar.setFillColor(sf::Color(200, 0, 0));
    hpBar.setSize(sf::Vector2f(hpShell.getSize().x, hpShell.getSize().y));
    
    UpdatePosition();
    if (gun.GetType() == Gun::Types::AK)
        maxDelayShooting = 35;
    else if (gun.GetType() == Gun::Types::Pistol)
        maxDelayShooting = 60;
}

void Enemy::Draw() {
    if (IsThisInsideWindow() && wasUpdated) {
        if (move.getAnimated())
            gamew->window->draw(move.sprite);
        else
            gamew->window->draw(body);
        gamew->window->draw(gun.GetSprite());
        gamew->window->draw(hand);
        blood.Draw();
        gamew->window->draw(hpShell);
        gamew->window->draw(hpBar);
        
    }
}

//std::chrono::microseconds Entity::total = std::chrono::microseconds(0);

void Enemy::Update() {
    // UpdateRotation();
    // move->Update();
    if (IsThisInsideWindow()) {
        
        wasUpdated = true;
        UpdatePosition();
        blood.Update();
        hpShell.setPosition(posRect.left - IDENTATION_AT_POSRECT_LEFT + gamew->offsetRelativeCenter.x,
                                         posRect.top - IDENTATION_AT_POSRECT_TOP - 10 + gamew->offsetRelativeCenter.y);
        hpBar.setPosition(posRect.left - IDENTATION_AT_POSRECT_LEFT + gamew->offsetRelativeCenter.x,
                                       posRect.top - IDENTATION_AT_POSRECT_TOP - 10 + gamew->offsetRelativeCenter.y);
        hpBarSize.x = (HP * hpShell.getSize().x) / 100;
        hpBarSize.y = hpShell.getSize().y;
        hpBar.setSize(hpBarSize);
        
        DetectPlayer();
        
        if (HP <= 0)
            deleteIt = true;
        
    }
    
}

void Enemy::DetectPlayer() {
    if (CheckTheRay()) {
        sf::Vector2f rayStart = {posRect.left, posRect.top};
        sf::Vector2f rayEnd = {gamew->player->posRect.left, gamew->player->posRect.top};
        sf::Vector2f direction = rayEnd - rayStart;
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 450) return;
        double tg = (direction.y / direction.x);
        float atg = atan(tg);
        if (direction.x >= 0) {
            if (flipped) {
                flipped = false;
                bodyRect.width = -bodyRect.width;
                bodyRect.left = bodyRect.left - abs(bodyRect.width);
                body.setTextureRect(bodyRect);

                handRect.width = -handRect.width;
                handRect.left = handRect.left - abs(handRect.width);
                hand.setOrigin(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
                hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
                hand.setTextureRect(handRect);

                auto tmp = gun.GetSprite().getTextureRect();
                tmp.width = -tmp.width;
                tmp.left = tmp.left - abs(tmp.width);
                gun.GetSprite().setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
                gun.GetSprite().setPosition(hand.getPosition());
                gun.GetSprite().setTextureRect(tmp);
            }
        }
        else {
            if (!flipped) {
                flipped = true;
                bodyRect.width = -bodyRect.width;
                bodyRect.left = bodyRect.left + abs(bodyRect.width);
                body.setTextureRect(bodyRect);

                handRect.width = -handRect.width;
                handRect.left = handRect.left + abs(handRect.width);
                hand.setOrigin(abs(handRect.width) - IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
                hand.setPosition((body.getPosition().x + abs(bodyRect.width)) - POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
                hand.setTextureRect(handRect);

                auto tmp = gun.GetSprite().getTextureRect();
                tmp.width = -tmp.width;
                tmp.left = tmp.left + abs(tmp.width);
                gun.GetSprite().setOrigin(abs(tmp.width) - IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
                gun.GetSprite().setPosition(hand.getPosition());
                gun.GetSprite().setTextureRect(tmp);
            }
        }
        hand.setRotation((atg * 180.0 / 3.1415));
        gun.GetSprite().setRotation((atg * 180.0 / 3.1415));
        if (delayShooting > maxDelayShooting){
            gun.Shoot(sf::Vector2f(posRect.left + POINT_HAND_X, posRect.top + POINT_HAND_Y - 4), -tg, this);
            delayShooting = 0;
        }
        else
            ++delayShooting;
        
    }
    
}

bool Enemy::CheckTheRay() {
    
    bool flag = true;
    // Создаем луч и точку начала луча (позиция бота)
    sf::Vector2f rayStart = {posRect.left + posRect.width / 2, posRect.top + 10};
    sf::Vector2f rayEnd = {gamew->player->posRect.left + gamew->player->posRect.width / 2,
                           gamew->player->posRect.top + gamew->player->posRect.height / 2};
    sf::Vector2f direction = rayEnd - rayStart;
    Section a {rayStart.x, rayStart.y, rayEnd.x, rayEnd.y};

    // Проверяем пересечение луча с препятствиями
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
        if ((*it)->isMovable() && (*it)->isCollidable()) {
            
            if ((*it)->Intersection(a)) {
                // Если есть пересечение, игрок не видим
                flag = false;
            }
            
        }
    }
    
    // Если нет пересечений с препятствиями, игрок видим
    return flag;
}



void Enemy::Hit(float posX, float posY, sf::Vector2f direction) {
    blood.StartSplash(posX, posY, direction);
    HP -= 25 + (rand() % 10) - 5;
}

void Enemy::UpdateDirection() {
    direction = sf::Vector2f(0, 0);
    direction += sf::Vector2f(0, GetFreeFall());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move.SetFlipped();
        direction += sf::Vector2f(-velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move.SetOrigin();
        direction += sf::Vector2f(velocity, 0);
    }
    CollideCheck();
    posRect.left += direction.x;
    posRect.top += direction.y;
    UpdatePosition();
}

void Enemy::UpdatePosition() {
    body.setPosition(posRect.left - IDENTATION_AT_POSRECT_LEFT + gamew->offsetRelativeCenter.x,
                     posRect.top - IDENTATION_AT_POSRECT_TOP + gamew->offsetRelativeCenter.y);
    if (!flipped)
        hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    else 
        hand.setPosition(body.getPosition().x + std::abs(bodyRect.width) - POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    gun.GetSprite().setPosition(hand.getPosition());
}

bool Enemy::IsThisInsideWindow() {
    if (posRect.left + posRect.width + gamew->offsetRelativeCenter.x < 0 || posRect.left + gamew->offsetRelativeCenter.x > gamew->window->getSize().x)
        return false;
    if (posRect.top + posRect.height + gamew->offsetRelativeCenter.y < 0 || posRect.top + gamew->offsetRelativeCenter.y > gamew->window->getSize().y)
        return false;
    return true;
}

float Enemy::GetFreeFall() {
    bool ff = CheckFreeFall();
    if (!isFalling && ff)
        isFalling = true, currSpeedFall = 2;
    else if (isFalling && ff) {
        if (currSpeedFall < 7) {
            currSpeedFall += gamew->pxPerFrameFall;
        }
        return currSpeedFall;
    } else
        isFalling = false;
    return 0;
}

bool Enemy::CheckFreeFall() {
    bool flag = true;
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
        if ((*it)->isMovable() && (*it)->isCollidable()) {
            if ((*it)->assumeCollideY(1, this->posRect)) {
                flag = false;
            }
        }
    }
    return flag;
}

void Enemy::CollideCheck() {
    int actionForX = (direction.x > 0.01 ? 1 : -1);
    int actionForY = (direction.y > 0.01 ? 1 : -1);
    bool flag = true;
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
        if ((*it)->isMovable()) {
            // Collision check
            if ((*it)->assumeCollideX(direction.x, this->posRect))
                flag = false;
        }
    }
    if (!flag) {
        int reduction = actionForX;
        flag = true;
        for (; abs(reduction) < abs(direction.x) && flag; reduction = reduction + actionForX) {
            for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
                if ((*it)->isMovable()) {
                    // Collision check
                    if ((*it)->assumeCollideX(reduction, this->posRect))
                        flag = false;
                }
            }
        }
        direction.x = reduction + (-actionForX * 2);
    }

    flag = true;
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
        if ((*it)->isMovable()) {
            // Collision check
            if ((*it)->assumeCollideY(direction.y, this->posRect))
                flag = false;
        }
    }
    if (!flag) {
        int reduction = actionForY;
        flag = true;
        for (; abs(reduction) < abs(direction.y) && flag; reduction = reduction + actionForY) {
            for (std::list<std::unique_ptr<Obj>>::iterator it = gamew->ObjList.begin(); it != gamew->ObjList.end() && flag; ++it) {
                if ((*it)->isMovable()) {
                    // Collision check
                    if ((*it)->assumeCollideY(reduction, this->posRect))
                        flag = false;
                }
            }
        }
        direction.y = reduction + (-actionForY * 2);
    }
}

void Enemy::UpdateRotation() {
    if (sf::Mouse::getPosition(*gamew->window).x - body.getPosition().x - POINT_HAND_X <= 0) {
        if (!flipped) {
            flipped = true;
            bodyRect.width = -bodyRect.width;
            bodyRect.left = bodyRect.left + abs(bodyRect.width);
            body.setTextureRect(bodyRect);

            handRect.width = -handRect.width;
            handRect.left = handRect.left + abs(handRect.width);
            hand.setOrigin(abs(handRect.width) - IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
            hand.setPosition((body.getPosition().x + abs(bodyRect.width)) - POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
            hand.setTextureRect(handRect);

            auto tmp = gun.GetSprite().getTextureRect();
            tmp.width = -tmp.width;
            tmp.left = tmp.left + abs(tmp.width);
            gun.GetSprite().setOrigin(abs(tmp.width) - IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
            gun.GetSprite().setPosition(hand.getPosition());
            gun.GetSprite().setTextureRect(tmp);
        }
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew->window).y) /
                    (sf::Mouse::getPosition(*gamew->window).x - (body.getPosition().x + abs(bodyRect.width) - POINT_HAND_X));
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
        gun.GetSprite().setRotation(-(atan(tg) * 180 / 3.1415));
    } else {
        if (flipped) {
            flipped = false;
            bodyRect.width = -bodyRect.width;
            bodyRect.left = bodyRect.left - abs(bodyRect.width);
            body.setTextureRect(bodyRect);

            handRect.width = -handRect.width;
            handRect.left = handRect.left - abs(handRect.width);
            hand.setOrigin(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
            hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
            hand.setTextureRect(handRect);

            auto tmp = gun.GetSprite().getTextureRect();
            tmp.width = -tmp.width;
            tmp.left = tmp.left - abs(tmp.width);
            gun.GetSprite().setOrigin(IDENTATION_AT_GUN_X, IDENTATION_AT_GUN_Y);
            gun.GetSprite().setPosition(hand.getPosition());
            gun.GetSprite().setTextureRect(tmp);
        }
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew->window).y) /
                    (sf::Mouse::getPosition(*gamew->window).x - (body.getPosition().x + POINT_HAND_X));
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
        gun.GetSprite().setRotation(-(atan(tg) * 180 / 3.1415));
    }
}
