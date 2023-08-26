#pragma once
#include <SFML/Graphics.hpp>
#include "Obj.hpp"
#include <memory>
#include <string>
#include <iostream>

class TextBox : public Obj
{
public:

    TextBox(sf::RenderWindow *window, sf::Font *font, const float x, const float y, const unsigned int fSize = 30, const float w = 200, const float h = 60);
    void Draw() override;
    void Update() override;
    void SetDrawCursor(bool v);
    void AppendLetter(wchar_t ch);
    void DelLetter();
    void ChangeText(std::wstring t);
    sf::RectangleShape &getRect();

private:

    void CheckWidthText();
    int posCursor;
    sf::RenderWindow *window;
    sf::Font *Geologica;
    sf::Text text;
    int maxWidth, h;
    sf::RectangleShape rect;
    sf::RectangleShape cursor;
    bool showCursor = true;
    sf::Clock cursorClock;
    bool drawCursor = false;
};


