#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include <random>

#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

class Background : public Obj
{
public:
    Background(sf::RenderWindow* window, sf::Font &font, bool isStatic = false);
    void SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown);
    void SetSingleColor(sf::Color color);
    void SetRandomGradient();
    void Draw() override;
    void Update() override;

private:

    void GenerateRandom();

    sf::Clock delay;
    bool isStatic;
    std::random_device rd;
    sf::RenderWindow* window;
    sf::Font &Geologica;
    sf::VertexArray V_A;
    sf::Color rUp, lUp, rDown, lDown;
    int min = 60, max = 255;
};