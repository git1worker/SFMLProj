#pragma once
#include <SFML/Graphics.hpp>

class Gamew;

class HandleEvent
{
public:
    HandleEvent(Gamew *gamew);
    void operator()(const sf::Event &event);

private:
    void eventMouseMoved(const sf::Event &event);
    void eventMouseButtonPressed(const sf::Event &event);
    void eventMouseButtonReleased(const sf::Event &event);
    void eventKeyPressed(const sf::Event &event);
    void eventKeyReleased(const sf::Event &event);
    void eventMouseWheelScrolled(const sf::Event &event);

    Gamew *gamew;
};
