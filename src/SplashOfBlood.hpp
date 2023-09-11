#pragma once
#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class SplashOfBlood : public Animation {
  public:
    SplashOfBlood() = default;
    SplashOfBlood(Gamew *gamew);
    void Draw() override;
    void Update() override;
    void StartSplash(float x, float y, sf::Vector2f direction);
    SplashOfBlood& operator=(const SplashOfBlood& other) = default;

  private:
    double orientation(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c);
    bool isInsideTriangle(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c, const sf::Vector2f &p);

    sf::Image image1, image2, image3;
    sf::Texture texture1, texture2, texture3;
    sf::Sprite sprite;
    
    sf::Vector2f pos;
};
