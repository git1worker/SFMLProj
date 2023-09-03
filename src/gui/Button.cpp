#include "Button.hpp"
#include <stdio.h>

int Button::counter = 0;

Button::Button(sf::RenderWindow *window, sf::Font *font, const float x, const float y, std::wstring stri)
    : str(stri), window(window), Geologica(font) {
    ++counter;
    posRect.left = x;
    posRect.top = y;
    posRect.width = 150, posRect.height = 50;
    rect = sf::RectangleShape(sf::Vector2f(posRect.width, posRect.height));
    rect.setOrigin(sf::Vector2f(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(sf::Color(160, 160, 160));
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(100, 100, 100));
    text = Label(window, font, stri, rect.getOrigin().x + rect.getGlobalBounds().left, rect.getOrigin().y + rect.getGlobalBounds().top,
                 Label::Align::Center, 25, 500);
    // printf("\n%f %f %f %f\n", rect->getGlobalBounds().left,
    // rect->getGlobalBounds().top, rect->getGlobalBounds().width,
    // rect->getGlobalBounds().height); printf("%f %f %f %f\n\n",
    // text.getGlobalBounds().left, text.getGlobalBounds().top,
    // text.getGlobalBounds().width, text.getGlobalBounds().height);
    ChangeText(str);
}

void Button::ChangeText(std::wstring t) { text.ChangeText(t); }

void Button::Release() {
    ChangeText(str);
    wasClicked = false;
}

bool Button::isHovered() { return hovered; }

void Button::SetHovered() {
    rect.setFillColor(sf::Color(180, 180, 180, 100));
    hovered = true;
}

void Button::ResetHovered() {
    rect.setFillColor(sf::Color(160, 160, 160, 100));
    hovered = false;
}

bool Button::getWasClicked() { return wasClicked; }

void Button::Draw() {
    window->draw(rect);
    text.Draw();
}

sf::RectangleShape &Button::getRect() { return rect; }

Label *Button::getLabel() { return &text; }