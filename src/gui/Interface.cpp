#include "Interface.hpp"
#include "../Gamew.hpp"


Interface::Interface(Gamew* gamew) : gamew(gamew) {
    hpL.getText().setFillColor(sf::Color(60, 60, 60));
    gunL.getText().setFillColor(sf::Color(60, 60, 60));
    
    hpShell.setOutlineColor(sf::Color::Black);
    hpShell.setOutlineThickness(2);
    hpShell.setFillColor(sf::Color(150, 150, 150, 100));
    hpShell.setSize(sf::Vector2f(100, hpL.getText().getCharacterSize()));
    hpShell.setPosition(sf::Vector2f(100, hpL.getText().getPosition().y));
    gunShell.setFillColor(sf::Color(150, 150, 150, 100));
    gunShell.setOutlineThickness(2);
    gunShell.setOutlineColor(sf::Color::Black);
    gunShell.setSize(sf::Vector2f(100, hpL.getText().getCharacterSize()));
    gunShell.setPosition(sf::Vector2f(100, gunL.getText().getPosition().y));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(hpShell.getSize().x, hpShell.getSize().y));
    hpBar.setPosition(sf::Vector2f(hpShell.getPosition().x, hpShell.getPosition().y));
}

Interface::~Interface() {

}

void Interface::Draw() {
    hpL.Draw();
    gunL.Draw();
    gamew->window->draw(hpShell);
    gamew->window->draw(gunShell);
    gamew->window->draw(hpBar);
}

void Interface::Update() {

}
