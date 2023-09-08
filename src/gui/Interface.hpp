#pragma once
#include "../Gamew.hpp"
#include "../Obj.hpp"
#include "Label.hpp"
#include <SFML/Graphics.hpp>

#define PADDING 20

class Interface : public Obj {
  public:
    Interface(Gamew *gamew);
    ~Interface();
    void Draw() override;
    void Update() override;

  private:
    Gamew *gamew;
    sf::Sprite currGun;
    sf::RectangleShape hpBar, gunBar, hpShell, gunShell;
    Label hpL{gamew->window.get(), &gamew->Geologica, L"HP", PADDING, PADDING, Label::Align::Left};
    Label gunL{gamew->window.get(), &gamew->Geologica, L"GUN", PADDING, PADDING * 3 + 30, Label::Align::Left};
    Label ammo{gamew->window.get(), &gamew->Geologica, L"999", 0, 0, Label::Align::Left, 25};
};