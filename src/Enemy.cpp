#include "Enemy.hpp"
#include "Gamew.hpp"

#include <cmath>

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2
#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)
#define IDENTATION_AT_POSRECT_LEFT 3
#define IDENTATION_AT_POSRECT_TOP 4

Enemy::Enemy(Gamew &gamew, sf::Vector2f spawn) : gamew(gamew) {

    type = Types::greenAgent;
    if (type == Types::armoredAgent) {
        textureBody.loadFromFile("../assets/img/characters/agent_2.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_gray.png");
        move = new AnimHuman(&gamew, "../assets/img/characters/anims_gray_agent.png", this);
    } else if (type == Types::greenAgent) {
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
        move = new AnimHuman(&gamew, "../assets/img/characters/anims_green_agent.png", this);
    }

    body.setTexture(textureBody);
    posRect.left = spawn.x + IDENTATION_AT_POSRECT_LEFT;
    posRect.top = spawn.y + IDENTATION_AT_POSRECT_TOP;
    posRect.width = body.getTextureRect().width - IDENTATION_AT_POSRECT_LEFT * 2;
    posRect.height = body.getTextureRect().height - IDENTATION_AT_POSRECT_TOP;
    body.setPosition(sf::Vector2f(spawn.x - POINT_HAND_X + gamew.offsetRelativeCenter.x, spawn.y - POINT_HAND_Y + gamew.offsetRelativeCenter.y));
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    gun.GetSprite().setPosition(hand.getPosition());
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

void Enemy::Draw() {
    if (IsThisInsideWindow()) {
        if (move->getAnimated())
            gamew.window->draw(move->sprite);
        else
            gamew.window->draw(body);
        gamew.window->draw(gun.GetSprite());
        gamew.window->draw(hand);
    }
}

void Enemy::Update() {
    // UpdateRotation();
    // move->Update();
    UpdatePosition();
    if (HP <= 0)
        deleteIt = true;
}

Enemy::~Enemy() { delete move; }

void Enemy::UpdateDirection() {
    direction = sf::Vector2f(0, 0);
    direction += sf::Vector2f(0, GetFreeFall());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move->SetFlipped();
        direction += sf::Vector2f(-velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move->SetOrigin();
        direction += sf::Vector2f(velocity, 0);
    }
    CollideCheck();
    posRect.left += direction.x;
    posRect.top += direction.y;
    UpdatePosition();
}

void Enemy::UpdatePosition() {
    body.setPosition(posRect.left - IDENTATION_AT_POSRECT_LEFT + gamew.offsetRelativeCenter.x,
                     posRect.top - IDENTATION_AT_POSRECT_TOP + gamew.offsetRelativeCenter.y);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    gun.GetSprite().setPosition(hand.getPosition());
}

bool Enemy::IsThisInsideWindow() {
    if (posRect.left + posRect.width + gamew.offsetRelativeCenter.x < 0 || posRect.left + gamew.offsetRelativeCenter.x > gamew.window->getSize().x)
        return false;
    if (posRect.top + posRect.height + gamew.offsetRelativeCenter.y < 0 || posRect.top + gamew.offsetRelativeCenter.y > gamew.window->getSize().y)
        return false;
    return true;
}

float Enemy::GetFreeFall() {
    bool ff = CheckFreeFall();
    if (!isFalling && ff)
        isFalling = true, currSpeedFall = 2;
    else if (isFalling && ff) {
        if (currSpeedFall < 7) {
            currSpeedFall += gamew.pxPerFrameFall;
        }
        return currSpeedFall;
    } else
        isFalling = false;
    return 0;
}

bool Enemy::CheckFreeFall() {
    bool flag = true;
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it) {
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
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it) {
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
            for (std::list<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it) {
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
    for (std::list<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it) {
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
            for (std::list<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it) {
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
    if (sf::Mouse::getPosition(*gamew.window).x - body.getPosition().x - POINT_HAND_X <= 0) {
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
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) /
                    (sf::Mouse::getPosition(*gamew.window).x - (body.getPosition().x + abs(bodyRect.width) - POINT_HAND_X));
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
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) /
                    (sf::Mouse::getPosition(*gamew.window).x - (body.getPosition().x + POINT_HAND_X));
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
        gun.GetSprite().setRotation(-(atan(tg) * 180 / 3.1415));
    }
}
