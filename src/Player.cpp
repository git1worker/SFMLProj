#include "Player.hpp"
#include "Debug.hpp"
#include "Gamew.hpp"
#include <cmath>
#include <iostream>

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2
#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)

Player::Player(Gamew &gamew, Types type, sf::Vector2f spawn) : gamew(gamew), spawn(spawn) {
    this->type = type;
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
    posRect.left = spawn.x + 3;
    posRect.top = spawn.y + 4;
    posRect.width = body.getTextureRect().width - 3 * 2;
    posRect.height = body.getTextureRect().height - 4;
    body.setPosition(sf::Vector2f(gamew.window->getSize().x / 2 - POINT_HAND_X, gamew.window->getSize().y / 2 - POINT_HAND_Y));
    gamew.offsetRelativeCenter.x = body.getPosition().x - spawn.x;
    gamew.offsetRelativeCenter.y = body.getPosition().y - spawn.y;
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    gun.GetSprite().setPosition(hand.getPosition());

    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

Player::~Player() { delete move; }

void Player::Shoot() { gun.Shoot(sf::Vector2f(posRect.left + POINT_HAND_X, posRect.top + POINT_HAND_Y - 4), this); }

void Player::Draw() {

    if (move->getAnimated())
        gamew.window->draw(move->sprite);
    else
        gamew.window->draw(body);
    gamew.window->draw(gun.GetSprite());
    gamew.window->draw(hand);
}

void Player::Update() {

    UpdateRotation();
    UpdateDirection();
    move->Update();
}

void Player::MoveStop() { move->Stop(); }

void Player::StartJump() {
    if (!jumping)
        energyJump = 15;
    jumping = true;
}

void Player::CollideCheck() {
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

void Player::CheckJump() {
    if (jumping) {
        direction.y -= energyJump--;
        if (energyJump == 0)
            jumping = false;
    }
}

void Player::UpdateDirection() {
    direction = sf::Vector2f(0, 0);
    direction += sf::Vector2f(0, GetFreeFall());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && CheckCanMoveUp()) {
        direction += sf::Vector2f(0, -currSpeedFall - velocity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move->SetFlipped();
        move->Start();
        direction += sf::Vector2f(-velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move->SetOrigin();
        move->Start();
        direction += sf::Vector2f(velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move->SetOrigin();
        move->Start();
        direction += sf::Vector2f(0, velocity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isFalling)
        StartJump();

    if (jumping)
        CheckJump();
    CollideCheck();
    posRect.left += direction.x;
    posRect.top += direction.y;
    gamew.offsetRelativeCenter.x -= direction.x;
    gamew.offsetRelativeCenter.y -= direction.y;
}

float Player::GetFreeFall() {
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

bool Player::CheckFreeFall() {
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

bool Player::CheckCanMoveUp() { return gamew.currTileMap->IsThereLadNearby(this->posRect); }

void Player::UpdateRotation() {
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
        tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) /
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
        tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) /
             (sf::Mouse::getPosition(*gamew.window).x - (body.getPosition().x + POINT_HAND_X));
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
        gun.GetSprite().setRotation(-(atan(tg) * 180 / 3.1415));
    }
}
