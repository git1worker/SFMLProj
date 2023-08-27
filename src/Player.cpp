#include "Player.hpp"
#include <cmath>
#include <iostream>

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2

#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)

Player::Player(sf::RenderWindow* window, Types type, sf::Vector2f spawn) : window(window), type(type), spawn(spawn)
{   
    if (type == Types::armoredAgent)
        textureBody.loadFromFile("../assets/img/characters/agent_2.png");
    else if (type == Types::greenAgent)
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
    body.setTexture(textureBody);
    body.setPosition(spawn);
    texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    // hand.setRotation(180);
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

void Player::Draw()
{
    window->draw(body);
    window->draw(hand);
}

void Player::Update()
{   
    if (sf::Mouse::getPosition(*window).x - body.getPosition().x < 0){
        if (!flipped){
            flipped = true;
            bodyRect.width = -bodyRect.width;
            handRect.width = -handRect.width;
            handRect.left = handRect.left + abs(handRect.width);
            bodyRect.left = bodyRect.left + abs(bodyRect.width);
            body.setTextureRect(bodyRect);
            hand.setOrigin(abs(handRect.width), IDENTATION_AT_HAND_Y);
            hand.setPosition((body.getPosition().x + abs(bodyRect.width)) - POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
            hand.setTextureRect(handRect);
            }
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
        
    }
    double tg = ((body.getPosition().y + POINT_HAND_Y) - sf::Mouse::getPosition(*window).y) / (sf::Mouse::getPosition(*window).x - (body.getPosition().x + POINT_HAND_X));
    std::cout << body.getPosition().x + POINT_HAND_X << ' ' << (body.getPosition().y + POINT_HAND_Y) << std::endl;
    hand.setRotation(-(atan(tg)*180 / 3.1415));
}
