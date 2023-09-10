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

class Background : public Obj, public Element {
  public:
    Background(sf::RenderWindow *window, sf::Font *font, bool isStaticGradient = false);
    Background(sf::RenderWindow *window, sf::Font *font, sf::Color color);
    void SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown);
    void SetSingleColor(sf::Color color);
    void SetRandomGradient();
    void SetTexture(const std::string filename);
    void Draw() override;
    void Update() override;
    void Update(const sf::Vector2f &offsetRelativeCenter) override;

  private:
    void GenerateRandom();

    
    sf::Clock delay;
    sf::RenderWindow *window;
    sf::Font *Geologica;
    bool isStaticGradient, isTextured;
    std::random_device rd;
    sf::VertexArray V_A;
    sf::Color rUp, lUp, rDown, lDown;
    int min = 60, max = 255;
    sf::Texture texture;
    sf::RectangleShape rect;
};