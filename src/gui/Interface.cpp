#include "Interface.hpp"
#include "../Gamew.hpp"
#include "../Gun.hpp"
#include "../Player.hpp"

Interface::Interface(Gamew *gamew) : gamew(gamew) {
    const int widthShell = 150;
    hpL.getText().setFillColor(sf::Color(60, 60, 60));
    gunL.getText().setFillColor(sf::Color(60, 60, 60));
    hpShell.setOutlineColor(sf::Color::Black);
    hpShell.setOutlineThickness(2);
    hpShell.setFillColor(sf::Color(150, 150, 150, 100));
    hpShell.setSize(sf::Vector2f(widthShell, hpL.getText().getCharacterSize() - hpL.getText().getCharacterSize() / 4));
    hpShell.setPosition(sf::Vector2f(100, hpL.getText().getPosition().y + hpL.getText().getCharacterSize() / 4));
    gunShell.setFillColor(sf::Color(150, 150, 150, 100));
    gunShell.setOutlineThickness(2);
    gunShell.setOutlineColor(sf::Color::Black);
    gunShell.setSize(sf::Vector2f(widthShell, 40));
    gunShell.setPosition(sf::Vector2f(100, gunL.getText().getPosition().y));
    hpBar.setFillColor(sf::Color(210, 0, 0));
    hpBar.setSize(sf::Vector2f(hpShell.getSize().x, hpShell.getSize().y));
    hpBar.setPosition(sf::Vector2f(hpShell.getPosition().x, hpShell.getPosition().y));
    currGun.setTexture(*Gun::GetTexture(gamew->player->gun.GetType()));
    currGun.setPosition(gunShell.getPosition().x + 1, gunShell.getPosition().y + 1);
    currGun.setScale(2, 2);
    ammo.posRect.left = currGun.getPosition().x + currGun.getGlobalBounds().width + 1;
    ammo.posRect.top = currGun.getPosition().y;
}

Interface::~Interface() {}

void Interface::Draw() {
    hpL.Draw();
    gunL.Draw();
    gamew->window->draw(hpShell);
    gamew->window->draw(gunShell);
    gamew->window->draw(hpBar);
    gamew->window->draw(currGun);
    ammo.Draw();
}

void Interface::Update() {
    hpBar.setSize(sf::Vector2f((gamew->player->HP * hpShell.getSize().x) / MAX_HP, hpShell.getSize().y));
    ammo.ChangeText(std::to_wstring(gamew->player->gun.ammo));
}
