#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include <random>

class Background : public Obj
{
public:
    Background(sf::RenderWindow* window, sf::Font &font);
    void SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown);
    void SetStatic(sf::Color color);
    void SetRandomGradient();
    void Draw() override;
    void Update() override;

private:

    void GenerateRandom();

    bool isStatic = false;
    std::random_device rd;
    sf::RenderWindow* window;
    sf::Font &Geologica;
    sf::VertexArray V_A;
    sf::RectangleShape backgroundColor;
    sf::Color rUp, lUp, rDown, lDown, singleColor;
    int min = 60, max = 255;
};