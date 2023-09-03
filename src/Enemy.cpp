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
    } else if (type == Types::greenAgent) {
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
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
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

void Enemy::Draw() {
    if (IsThisInsideWindow()) {
        gamew.window->draw(body);
        gamew.window->draw(hand);
    }
}

void Enemy::Update() { UpdateDirection(); }

Enemy::~Enemy() {}

void Enemy::UpdateDirection() { UpdatePosition(); }

void Enemy::UpdatePosition() {
    body.setPosition(posRect.left - IDENTATION_AT_POSRECT_LEFT + gamew.offsetRelativeCenter.x, 
                     posRect.top - IDENTATION_AT_POSRECT_TOP + gamew.offsetRelativeCenter.y);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
}

bool Enemy::IsThisInsideWindow() {
    if (posRect.left + posRect.width + gamew.offsetRelativeCenter.x < 0 || posRect.left + gamew.offsetRelativeCenter.x > gamew.window->getSize().x)
        return false;
    if (posRect.top + posRect.height + gamew.offsetRelativeCenter.y < 0 || posRect.top + gamew.offsetRelativeCenter.y > gamew.window->getSize().y)
        return false;
    return true;
}
