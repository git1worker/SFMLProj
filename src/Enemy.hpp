#pragma once
#include "AnimHuman.hpp"
#include "Entity.hpp"
#include "Gun.hpp"
#include "SplashOfBlood.hpp"
#include <SFML/Graphics.hpp>
#include "Section.hpp"

class Gamew;

class Enemy : public Entity {
  public:


    Enemy(Gamew &gamew, sf::Vector2f spawn);
    void Draw() override;
    void Update() override;
    void Hit(float posX, float posY, sf::Vector2f direction) override;
    ~Enemy();

  private:
    void UpdateDirection();
    void UpdatePosition();
    bool IsThisInsideWindow();
    float GetFreeFall();
    bool CheckFreeFall();
    void CollideCheck();
    void UpdateRotation();
    void DetectPlayer();
    bool CheckTheRay();

    Gamew &gamew;
    sf::Sprite body, hand;
    sf::Texture textureBody;

    sf::Texture texHand;
    sf::IntRect bodyRect, handRect;

    bool wasUpdated = false;
    sf::RectangleShape hpBar, hpShell;
    SplashOfBlood *blood;
    AnimHuman *move;
    bool animated = false;
    int delayShooting = 0;
    float currSpeedFall = 2;
    bool isFalling = false;
    Gun gun{Gun::Types::Pistol, gamew};
    static int randCnt;
    int maxDelayShooting;
};