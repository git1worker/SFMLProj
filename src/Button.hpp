#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Gamew.hpp"
#include "Label.hpp"
#include <iostream>
#include "Obj.hpp"
#include <functional>
#include <string>

#define DEBUG {std::cout << "Line: " << __LINE__ << std::endl; }

class Button : public Obj
{
public:
    Button(sf::RenderWindow* window, sf::Font &font, const float x = 500, const float y = 500, std::wstring str = L"Button");
    
    sf::RectangleShape &getRect();
    Label *getLabel();
    void Draw() override;
    bool getWasClicked();

    void Click(void (*callback)());
    void Click(std::function<void(void)> lambda);
    void Release();
    bool isHovered();
    void SetHovered();
    void ResetHovered();
    void ChangeText(std::wstring t);

private:
    bool hovered = false;
    bool wasClicked = false;
    std::unique_ptr<sf::RectangleShape> rect;
    std::unique_ptr<Label> text;
    std::wstring str;
    float wT, hT;
    sf::RenderWindow* window;
    sf::Font &Geologica;

};