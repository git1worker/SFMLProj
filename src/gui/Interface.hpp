#pragma once
#include <SFML/Graphics.hpp>
#include "../Obj.hpp"
#include "Label.hpp"
#include "../Gamew.hpp"

#define PADDING 20

class Interface : public Obj{
public:
    Interface(Gamew* gamew);
    ~Interface();
    void Draw() override;
    void Update() override;

private:

    Gamew* gamew;
    sf::RectangleShape hpBar, gunBar, hpShell, gunShell;
    Label hpL{gamew->window.get(), &gamew->Geologica, L"HP", PADDING, PADDING, Label::Align::Left};
    Label gunL{gamew->window.get(), &gamew->Geologica, L"GUN", PADDING, PADDING * 2 + 30, Label::Align::Left};
};