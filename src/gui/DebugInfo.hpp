#pragma once
#include "../Obj.hpp"
#include "Label.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

class Gamew;

class DebugInfo : public Obj {
  public:
    DebugInfo(Gamew *gamew, sf::Font *font, sf::Event *event);
    void UpdateFps(float fps);
    void Update();
    void Draw() override;

  private:
    float fps;
    std::wstringstream ss;
    Gamew *gamew;
    sf::Font *Geologica;
    Label info;
    sf::Event *event;
    float maxWidth = 200;
};