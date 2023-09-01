#include "Player.hpp"
#include <cmath>
#include <iostream>
#include "Gamew.hpp"
#include "Debug.hpp"

#define IDENTATION_AT_HAND_X 2
#define IDENTATION_AT_HAND_Y 2
#define POINT_HAND_X (10 + IDENTATION_AT_HAND_X)
#define POINT_HAND_Y (25 + IDENTATION_AT_HAND_Y)

Player::Player(Gamew &gamew, Types type, sf::Vector2f spawn) : gamew(gamew), spawn(spawn)
{   
    this->type = type;
    if (type == Types::armoredAgent)
    {
        textureBody.loadFromFile("../assets/img/characters/agent_2.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_gray.png");
        move = new Animation(&gamew, "../assets/img/characters/anims_gray_agent.png", 110);
    }
    else if (type == Types::greenAgent)
    {
        textureBody.loadFromFile("../assets/img/characters/agent_1.png");
        texHand.loadFromFile("../assets/img/characters/right_hand_green.png");
        move = new Animation(&gamew, "../assets/img/characters/anims_green_agent.png", 110);
    }
    body.setTexture(textureBody);
    body.setPosition(sf::Vector2f(gamew.window->getSize().x / 2 - POINT_HAND_X, gamew.window->getSize().y / 2 - POINT_HAND_Y));
    posRect.left = body.getPosition().x + 3;
    posRect.top = body.getPosition().y + 4;
    posRect.width = body.getTextureRect().width - 3 * 2;
    posRect.height = body.getTextureRect().height - 4;
    gamew.offsetRelativeCenter.x = spawn.x + body.getPosition().x + POINT_HAND_X;
    gamew.offsetRelativeCenter.y = spawn.y + body.getPosition().y + POINT_HAND_Y;
    hand.setTexture(texHand);
    hand.setPosition(body.getPosition().x + POINT_HAND_X, body.getPosition().y + POINT_HAND_Y);
    hand.setOrigin(sf::Vector2f(IDENTATION_AT_HAND_X, IDENTATION_AT_HAND_Y));
    bodyRect = body.getTextureRect();
    handRect = hand.getTextureRect();
}

Player::~Player()
{
    delete move;
}

void Player::Draw()
{

    if (move->getAnimated())
        gamew.window->draw(move->sprite);
    else
        gamew.window->draw(body);
    gamew.window->draw(hand);
}

// void Player::HandleMovement()
// {
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && gamew.currentWindow != Windows::MainW)
//     {
//         MovePlayerUp();
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && gamew.currentWindow != Windows::MainW)
//     {
//         MovePlayerLeft();
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && gamew.currentWindow != Windows::MainW)
//     {
//         MovePlayerDown();
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && gamew.currentWindow != Windows::MainW)
//     {
//         MovePlayerRight();
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gamew.currentWindow != Windows::MainW)
//     {
//         MovePlayerJump();
//     }
// }

void Player::Update()
{
    if (sf::Mouse::getPosition(*gamew.window).x - body.getPosition().x - POINT_HAND_X <= 0)
    {
        if (!flipped)
        {
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
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
        // std::cout << body.getPosition().x - body.getTextureRect().width + POINT_HAND_X << std::endl;
    }
    else
    {
        if (flipped)
        {
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
        // std::cout << body.getPosition().x + POINT_HAND_X << ' ' << (body.getPosition().y + POINT_HAND_Y) << std::endl;
        hand.setRotation(-(atan(tg) * 180 / 3.1415));
    }
    
    move->sprite.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y));
    UpdateDirection();
}

void Player::MoveStop()
{
    move->Stop();
}

void Player::MovePlayerJump()
{
    
}

void Player::CollideCheck()
{   
    int actionForX = (direction.x > 0.01 ? 1 : -1);
    int actionForY = (direction.y > 0.01 ? 1 : -1);
    bool flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
    {
        if ((*it)->isMovable())
        {
            // Collision check
            if ((*it)->assumeCollideX(direction.x, this->posRect))
                flag = false;
        }
    }
    if (!flag)
    {
        int reduction = actionForX;
        flag = true;
        for (; abs(reduction) < abs(direction.x) && flag; reduction = reduction + actionForX)
        {
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
            {
                if ((*it)->isMovable())
                {
                    // Collision check
                    if ((*it)->assumeCollideX(reduction, this->posRect))
                        flag = false;
                }
            }
        }
        direction.x = reduction + (-actionForX * 2);
    }

    flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
    {
        if ((*it)->isMovable())
        {
            // Collision check
            if ((*it)->assumeCollideY(direction.y, this->posRect))
                flag = false;
        }
    }
    if (!flag)
    {
        int reduction = actionForY;
        flag = true;
        for (; abs(reduction) < abs(direction.y) && flag; reduction = reduction + actionForY)
        {
            for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
            {
                if ((*it)->isMovable())
                {
                    // Collision check
                    if ((*it)->assumeCollideY(reduction, this->posRect))
                        flag = false;
                }
            }
        }
        direction.y = reduction + (-actionForY * 2);
    }
    
}

void Player::CollideCheckV2()
{
    int summ = round(abs(direction.x));
    int actionForX = (direction.x > 0.01 ? -1 : 1);
    int actionForY = (direction.y > 0.01 ? -1 : 1);
    bool flag = false;
    while (summ != 0 && !flag){
        flag = true;
        for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
        {
            if ((*it)->isMovable() && (*it)->isCollidable())
            {
                // Selection of the smallest allowable offset.
                // Need to finish this part !!! And all directions of moving !!!
                if ((*it)->assumeCollideX(direction.x, this->posRect)){
                    --summ;
                    if (summ != 0)
                        direction.x = direction.x + (direction.x / summ) * actionForX, flag = false;
                    else direction.x = 0, flag = true;
                    
                }
            }
        }
    }
    flag = false;
    summ = round(abs(direction.y));
    while (summ != 0 && !flag){
        flag = true;
        for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
        {
            if ((*it)->isMovable() && (*it)->isCollidable())
            {
                // Selection of the smallest allowable offset.
                // Need to finish this part !!! And all directions of moving !!!
                if ((*it)->assumeCollideY(direction.y, this->posRect)){
                    --summ;
                    if (summ != 0)
                        direction.y = direction.y + (direction.y / summ) * actionForY, flag = false;
                    else direction.y = 0, flag = true;
                    
                }
            }
        }
    }
}

void Player::UpdateDirection()
{   
    direction = sf::Vector2f(0,0);
    direction += sf::Vector2f(0, GetFreeFall());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        direction += sf::Vector2f(0, -currSpeedFall - velocity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        move->PlayFlipped();
        direction += sf::Vector2f(-velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        move->PlayOrigin();
        direction += sf::Vector2f(velocity, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isFalling)
        MovePlayerJump();
        
    
    CollideCheck();
    gamew.offsetRelativeCenter.x -= direction.x;
    gamew.offsetRelativeCenter.y -= direction.y;
}

float Player::GetFreeFall()
{   
    bool ff = CheckFreeFall();
    if (!isFalling && ff)
        isFalling = true, currSpeedFall = 2;  
    else if (isFalling && ff){
        if (currSpeedFall < 7){
            currSpeedFall += gamew.pxPerFrameFall;
        }
        return currSpeedFall;
    }
    else 
        isFalling = false;
    return 0;
}

bool Player::CheckFreeFall()
{   
    bool flag = true;
    for (std::vector<std::unique_ptr<Obj>>::iterator it = gamew.ObjVector.begin(); it != gamew.ObjVector.end() && flag; ++it)
    {
        if ((*it)->isMovable() && (*it)->isCollidable())
        {
            if ((*it)->assumeCollideY(1, this->posRect)){
                flag = false;
            }
        }
    }
    return flag;
}
