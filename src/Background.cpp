#include "Background.hpp"
#include <iostream>

using sf::Vector2f;

Background::Background(sf::RenderWindow *window, sf::Font &font) : window(window), Geologica(font)
{   
    V_A.setPrimitiveType(sf::Quads);
    GenerateRandom();
    V_A.append(sf::Vertex(Vector2f(0, 0), lUp));
    V_A.append(sf::Vertex(Vector2f(0, window->getSize().y), rUp));
    V_A.append(sf::Vertex(Vector2f(window->getSize().x, window->getSize().y), rDown));
    V_A.append(sf::Vertex(Vector2f(window->getSize().x, 0), lDown));
}

void Background::SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown)
{
    this->lUp = lUp, this->rUp = rUp, this->rDown = rDown, this->lDown = lDown;
    
}

void Background::SetRandomGradient(){
    isStatic = false;
    GenerateRandom();
    SetGradient(lUp, rUp, rDown, lDown);
}


void Background::Update(){
    if (!isStatic){
        std::mt19937 gen(rd());
        int r, g, b;
        std::uniform_int_distribution<int> dis(-1, 1);
        sf::Color* tmpArr[4] {&lUp, &rUp, &rDown, &lDown};
        for (int i = 0; i < 4; ++i){
            r = dis(gen);
            g = dis(gen);
            b = dis(gen);
            if (tmpArr[i]->r + r > max || tmpArr[i]->r + r < min)
                tmpArr[i]->r -= r;
            else 
                tmpArr[i]->r += r;
            if (tmpArr[i]->g + g > max || tmpArr[i]->g + g < min)
                tmpArr[i]->g -= g;
            else 
                tmpArr[i]->g += g;
            if (tmpArr[i]->b + b > max || tmpArr[i]->b + b < min)
                tmpArr[i]->b -= b;
            else 
                tmpArr[i]->b += b;
            V_A[i].color = *(tmpArr[i]);
        }
    }
    
    //std::cout << (int)V_A[0].color.r << std::endl; 
}

void Background::GenerateRandom()
{   
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    lUp = sf::Color(dis(gen), dis(gen), dis(gen));
    rUp = sf::Color(dis(gen), dis(gen), dis(gen));
    rDown = sf::Color(dis(gen), dis(gen), dis(gen));
    lDown = sf::Color(dis(gen), dis(gen), dis(gen));
}

void Background::Draw()
{   
    if (!isStatic)
        window->draw(V_A);
    else
        window->draw(backgroundColor);
}

void Background::SetStatic(sf::Color color)
{   
    singleColor = color;
    isStatic = true;
    backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    backgroundColor.setFillColor(color);
}
