#pragma once
#include "Element.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>

class TextBox : public Element {
  public:
    TextBox(sf::RenderWindow *window, sf::Font *font, const float x, const float y, const unsigned int fSize = 30, const float w = 200,
            const float h = 60);
    void Draw() override;
    void Update() override;
    void SetDrawCursor(bool v);
    void AppendLetter(wchar_t ch);
    void DelLetter();
    void ChangeText(std::wstring t);
    sf::RectangleShape &getRect();
    void HandleTextbox(const sf::Event &event);

  private:
    void CheckWidthText();
    int posCursor;
    sf::RenderWindow *window;
    sf::Font *Geologica;
    sf::Text text;
    sf::RectangleShape rect;
    sf::RectangleShape cursor;
    bool showCursor = true;
    sf::Clock cursorClock;
    bool drawCursor = false;
};
