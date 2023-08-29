#include "Player.hpp"
#include <cmath>
#include <iostream>
#include "Gamew.hpp"

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2

#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)

Player::Player(Gamew& gamew, Types type, sf::Vector2f spawn) : gamew(gamew), type(type), spawn(spawn)
{   
    if (type == Types::armoredAgent){
        textureBody.loadFromFile("../assets/img/characters/agent_2.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_gray.png");
    }
    else if (type == Types::greenAgent){
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
    }
    body.setTexture(textureBody);
    body.setPosition(sf::Vector2f(gamew.window->getSize().x / 2 - POINT_HAND_X, gamew.window->getSize().y / 2 - POINT_HAND_Y));
    posRect.left = body.getPosition().x;
    posRect.top = body.getPosition().y;
    posRect.width = body.getTextureRect().width;
    posRect.height = body.getTextureRect().height;
    gamew.offsetRelativeCenter.x = spawn.x + body.getPosition().x + POINT_HAND_X;
    gamew.offsetRelativeCenter.y = spawn.y + body.getPosition().y + POINT_HAND_Y;
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

void Player::Draw()
{
    gamew.window->draw(body);
    gamew.window->draw(hand);
}

void Player::Update()
{   
    if (sf::Mouse::getPosition(*gamew.window).x - body.getPosition().x - POINT_HAND_X <= 0){
        if (!flipped){
            flipped = true;
            bodyRect.width = -bodyRect.width;
            handRect.width = -handRect.width;
            handRect.left = handRect.left + abs(handRect.width);
            bodyRect.left = bodyRect.left + abs(bodyRect.width);
            body.setTextureRect(bodyRect);
            hand.setOrigin(abs(handRect.width) - IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
            hand.setPosition((body.getPosition().x + abs(bodyRect.width)) - POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
            hand.setTextureRect(handRect);
            }
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) / (sf::Mouse::getPosition(*gamew.window).x - (body.getPosition().x - body.getTextureRect().width + POINT_HAND_X));
        hand.setRotation(-(atan(tg)*180 / 3.1415));
        //std::cout << body.getPosition().x - body.getTextureRect().width + POINT_HAND_X << std::endl;
    }
    else {
        if (flipped) {
            flipped = false;            
            bodyRect.width = -bodyRect.width;
            handRect.width = -handRect.width;
            handRect.left = handRect.left - abs(handRect.width);
            bodyRect.left = bodyRect.left - abs(bodyRect.width);
            body.setTextureRect(bodyRect);
            hand.setOrigin(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y);
            hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
            hand.setTextureRect(handRect);
        }
        double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*gamew.window).y) / (sf::Mouse::getPosition(*gamew.window).x - (body.getPosition().x + POINT_HAND_X));
        //std::cout << body.getPosition().x + POINT_HAND_X << ' ' << (body.getPosition().y + POINT_HAND_Y) << std::endl;
        hand.setRotation(-(atan(tg)*180 / 3.1415));
    }
    
}

void Player::MovePlayerUp()
{
    bool flag = true;
    int reduction = 0;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
        if ((*it)->isMovable()){
            // Collision check
            if ((*it)->assumeCollide(sf::Vector2f(0, (this->velocity)), this->posRect)) 
                flag = false;
            
        }
    }
    if (flag)
        gamew.offsetRelativeCenter.y += this->velocity;
    else {
        int reduction = 1;
        flag = true;
        for (; reduction < this->velocity && flag; ++reduction){
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
                if ((*it)->isMovable()){
                    // Collision check
                    if ((*it)->assumeCollide(sf::Vector2f(0, reduction), this->posRect)) 
                        flag = false;
                }
            }
        }
        gamew.offsetRelativeCenter.y += reduction - 2;
    }
}

void Player::MovePlayerLeft()
{
    bool flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
        if ((*it)->isMovable()){
            // Collision check
            if ((*it)->assumeCollide(sf::Vector2f(this->velocity, 0), this->posRect)) flag = false;
        }
    }
    if (flag)
        gamew.offsetRelativeCenter.x += this->velocity;
    else {
        int reduction = 1;
        flag = true;
        for (; reduction < this->velocity && flag; ++reduction){
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
                if ((*it)->isMovable()){
                    // Collision check
                    if ((*it)->assumeCollide(sf::Vector2f(reduction, 0), this->posRect)) 
                        flag = false;
                }
            }
        }
        gamew.offsetRelativeCenter.x += reduction - 2;
    }
}

void Player::MovePlayerDown()
{
    bool flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
        if ((*it)->isMovable()){
            // Collision check
            if ((*it)->assumeCollide(sf::Vector2f(0, -this->velocity), this->posRect)) 
                flag = false;
        }
    }
    if (flag)
        gamew.offsetRelativeCenter.y -= this->velocity;
    else {
        int reduction = 1;
        flag = true;
        for (; reduction < this->velocity && flag; ++reduction){
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
                if ((*it)->isMovable()){
                    // Collision check
                    if ((*it)->assumeCollide(sf::Vector2f(0, -reduction), this->posRect)) 
                        flag = false;
                }
            }
        }
        gamew.offsetRelativeCenter.y -= reduction - 2;
        
    }
}

void Player::MovePlayerRight()
{
    bool flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
        if ((*it)->isMovable()){
            // Collision check
            if ((*it)->assumeCollide(sf::Vector2f(-this->velocity, 0), this->posRect)) flag = false;
        }
    }
    if (flag)
        gamew.offsetRelativeCenter.x -= this->velocity;
    else {
        int reduction = 1;
        flag = true;
        for (; reduction < this->velocity && flag; ++reduction){
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it){
                if ((*it)->isMovable()){
                    // Collision check
                    if ((*it)->assumeCollide(sf::Vector2f(-reduction, 0), this->posRect)) 
                        flag = false;
                }
            }
        }
        gamew.offsetRelativeCenter.x -= reduction - 2;
        
    }
}