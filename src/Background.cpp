#include "Background.hpp"
#include <iostream>
#include "Gamew.hpp"

#pragma GCC optimize("O0")

using sf::Vector2f;

Background::Background(Gamew* gamew, bool isStaticGradient)
    : gamew(gamew), isStaticGradient(isStaticGradient) {
    V_A.setPrimitiveType(sf::Quads);
    if (!isStaticGradient)
        GenerateRandom();
    V_A.append(sf::Vertex(Vector2f(0, 0), lUp));
    V_A.append(sf::Vertex(Vector2f(0, gamew->window->getSize().y), rUp));
    V_A.append(sf::Vertex(Vector2f(gamew->window->getSize().x, gamew->window->getSize().y), rDown));
    V_A.append(sf::Vertex(Vector2f(gamew->window->getSize().x, 0), lDown));
}

Background::Background(Gamew* gamew, sf::Color color) 
    : gamew(gamew) {
    isTextured = true;
    isStaticGradient = true;
    rect = sf::RectangleShape(sf::Vector2f(gamew->window->getSize().x, gamew->window->getSize().y));
    rect.setFillColor(color);
}

void Background::SetGradient(sf::Color lUp, sf::Color rUp, sf::Color rDown, sf::Color lDown) {
    this->lUp = lUp, this->rUp = rUp, this->rDown = rDown, this->lDown = lDown;
    V_A[0] = (sf::Vertex(Vector2f(0, 0), lUp));
    V_A[1] = (sf::Vertex(Vector2f(0, gamew->window->getSize().y), rUp));
    V_A[2] = (sf::Vertex(Vector2f(gamew->window->getSize().x, gamew->window->getSize().y), rDown));
    V_A[3] = (sf::Vertex(Vector2f(gamew->window->getSize().x, 0), lDown));
}

void Background::SetRandomGradient() {
    isStaticGradient = false;
    GenerateRandom();
    SetGradient(lUp, rUp, rDown, lDown);
}

void Background::Update() {
    rect.setTextureRect(sf::IntRect(sf::Vector2i(-gamew->offsetRelativeCenter.x, -gamew->offsetRelativeCenter.y),
                                    sf::Vector2i(rect.getTextureRect().width, rect.getTextureRect().height)));

    if (!isStaticGradient) {
        if (delay.getElapsedTime().asMilliseconds() < 100)
            return;
        delay.restart();
        std::mt19937 gen(rd());
        int change;
        std::uniform_int_distribution<int> dis(-1, 1);
        sf::Color *tmpArr[4]{&lUp, &rUp, &rDown, &lDown};
        for (int i = 0; i < 4; ++i) {
            change = dis(gen);
            if (tmpArr[i]->r + change > max || tmpArr[i]->r + change < min)
                tmpArr[i]->r -= change;
            else
                tmpArr[i]->r += change;
            if (tmpArr[i]->g + change > max || tmpArr[i]->g + change < min)
                tmpArr[i]->g -= change;
            else
                tmpArr[i]->g += change;
            if (tmpArr[i]->b + change > max || tmpArr[i]->b + change < min)
                tmpArr[i]->b -= change;
            else
                tmpArr[i]->b += change;
            V_A[i].color = *(tmpArr[i]);
        }
    }

    // std::cout << (int)V_A[0].color.r << std::endl;
}

void Background::GenerateRandom() {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    lUp = sf::Color(dis(gen), dis(gen), dis(gen));
    rUp = sf::Color(dis(gen), dis(gen), dis(gen));
    rDown = sf::Color(dis(gen), dis(gen), dis(gen));
    lDown = sf::Color(dis(gen), dis(gen), dis(gen));
}

void Background::Draw() {
    if (!isTextured)
        gamew->window->draw(V_A);
    else
        gamew->window->draw(rect);
}

void Background::SetSingleColor(sf::Color color) {
    isStaticGradient = true;
    V_A.append(sf::Vertex(Vector2f(0, 0), color));
    V_A.append(sf::Vertex(Vector2f(0, gamew->window->getSize().y), color));
    V_A.append(sf::Vertex(Vector2f(gamew->window->getSize().x, gamew->window->getSize().y), color));
    V_A.append(sf::Vertex(Vector2f(gamew->window->getSize().x, 0), color));
}

void Background::SetTexture(const std::string filename) {
    isTextured = true;
    isStaticGradient = false;
    texture = sf::Texture();
    if (!texture.loadFromFile(filename))
        std::cerr << "Could not load texture of background.", exit(1);
    rect = sf::RectangleShape(sf::Vector2f(gamew->window->getSize().x, gamew->window->getSize().y));
    rect.setTexture(&texture);
    rect.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(gamew->window->getSize().x, gamew->window->getSize().y)));
    movable = true;
}

#pragma GCC optimize("O3")