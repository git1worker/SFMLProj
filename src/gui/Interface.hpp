#pragma once
#include "Element.hpp"
#include "Label.hpp"
#include <SFML/Graphics.hpp>

#define PADDING 20

class Gamew;

class Interface : public Element {
  public:
    Interface(Gamew *gamew);
    ~Interface();
    void Draw() override;
    void Update() override;

  private:
    Gamew *gamew;
    sf::Sprite currGun;
    sf::RectangleShape hpBar, gunBar, hpShell, gunShell;
    Label hpL;
    Label gunL;
    Label ammo;
};