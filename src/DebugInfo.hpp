#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Label.hpp"

class DebugInfo : public Obj {
public:

    DebugInfo(sf::RenderWindow* window, sf::Font &font, sf::Event* event);
    void Update(sf::Event* event);
    void Draw() override;

private:
    sf::RenderWindow* window;
    sf::Font &Geologica;
    std::unique_ptr<Label> info;
    sf::Event* event;
    float maxWidth = 200;
    sf::Event::MouseMoveEvent lastMEvent{};
}; 