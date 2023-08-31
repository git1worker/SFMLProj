#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

int main()
{
    // const int fps = 60;
    // const int heightTile = 32;
    // sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(500, 500), "test");
    // sf::Texture tmp;
    // tmp.loadFromFile("../assets/img/characters/agent_1.png");
    // sf::Texture tmp2;
    // tmp2.loadFromFile("../assets/img/characters/agent_2.png");
    // sf::Sprite player(tmp);
    // auto t = player.getTextureRect();
    // player.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
    // player.setTextureRect(t);
    // window.setFramerateLimit(fps);

    // sf::Event event;
    // bool isActive = true;
    // sf::Vector2f offsetRelativeCenter{};
    // const float freeFall = 9.8;
    // const float pxPerFrame = (freeFall * heightTile) / fps;

    // sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 25));
    // floor.setPosition(sf::Vector2f(0, window.getSize().y - 50));
    // floor.setFillColor(sf::Color(0,0,0));

    // sf::Sprite a(tmp2);
    // a.setPosition(sf::Vector2f(window.getSize().x/3 + offsetRelativeCenter.x, window.getSize().y/3 + offsetRelativeCenter.y));
    // a.setTextureRect(t);

    // sf::FloatRect f{};
    // sf::FloatRect s{};

    // while (isActive)
    // {

    //     while (window.pollEvent(event)){
    //         if (event.type == sf::Event::Closed)
    //             isActive = false;
    //         if (event.type == sf::Event::KeyPressed){
    //             if (event.key.code == sf::Keyboard::Escape)
    //                 isActive = false;
    //         }
    //     }

    //     a.setPosition(sf::Vector2f(a.getPosition().x, a.getPosition().y + pxPerFrame));
    //     f.left = a.getPosition().x;
    //     f.top = a.getPosition().y;
    //     f.width = a.getTextureRect().width;
    //     f.height = a.getTextureRect().height;
    //     s.left = floor.getPosition().x;
    //     s.top = floor.getPosition().y;
    //     s.width = floor.getSize().x;
    //     s.height = floor.getSize().y;

    //     if (f.intersects(s))
    //         a.setPosition(sf::Vector2f(a.getPosition().x, a.getPosition().y - pxPerFrame));

    //     window.clear(sf::Color(255, 255, 255));
    //     window.draw(player);
    //     window.draw(floor);
    //     window.draw(a);

    //     window.display();
    // }

    return 0;
}