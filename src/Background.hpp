#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include "gui/Element.hpp"

#ifndef DEBUG
#define DEBUG                                                                                                                                        \
    { std::cout << "Line: " << __LINE__ << std::endl; }
#endif // DEBUG

class Gamew;

class Background : public Obj, public Element {
  public:
    Background(Gamew* gamew, bool isStaticGradient = false);
    Background(Gamew* gamew, sf::Color color);
    void SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown);
    void SetSingleColor(sf::Color color);
    void SetRandomGradient();
    void SetTexture(const std::string filename);
    void Draw() override;
    void Update() override;

  private:
    void GenerateRandom();

    Gamew* gamew;
    sf::Clock delay;
    sf::RenderWindow *window;
    bool isStaticGradient, isTextured;
    std::random_device rd;
    sf::VertexArray V_A;
    sf::Color rUp, lUp, rDown, lDown;
    int min = 60, max = 255;
    sf::Texture texture;
    sf::RectangleShape rect;
};