#pragma once
#include "../Gamew.hpp"
#include "Element.hpp"
#include "Label.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#ifndef DEBUG
#define DEBUG                                                                                                                                        \
    { std::cout << "Line: " << __LINE__ << std::endl; }
#endif // DEBUG

class Button : public Element {
  public:
    Button(sf::RenderWindow *window, sf::Font *font, const float x = 500, const float y = 500, std::wstring str = L"Button", const float width = 150, const float height = 50);

    sf::RectangleShape &getRect();
    Label *getLabel();
    void Draw() override;
    bool getWasClicked();

    template <typename T> void Click(T callback) { callback(), wasClicked = true; }

    void Release();
    bool isHovered();
    void SetHovered();
    void ResetHovered();
    void ChangeText(std::wstring t);

  private:
    static int counter;

    bool hovered = false;
    bool wasClicked = false;
    sf::RectangleShape rect;
    Label text;
    std::wstring str;
    float wT, hT;
    sf::RenderWindow *window;
    sf::Font *Geologica;
};
