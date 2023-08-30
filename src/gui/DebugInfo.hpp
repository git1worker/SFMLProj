#pragma once
#include "../Obj.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Label.hpp"
#include <sstream>

class DebugInfo : public Obj {
public:

    DebugInfo(sf::RenderWindow* window, sf::Font *font, sf::Event* event);
    void UpdateEvents(sf::Event* event);
    void UpdateFps(float fps);
    void Update();
    void Draw() override;

private:
    
    float fps;
    std::wstringstream ss;
    sf::RenderWindow* window;
    sf::Font *Geologica;
    Label info;
    sf::Event* event;
    float maxWidth = 200;
    sf::Event::MouseMoveEvent lastMEvent{};
}; 