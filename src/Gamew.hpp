#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "DebugInfo.hpp"

#define DEBUG {std::cout << "Line: " << __LINE__ << std::endl; }

using std::unique_ptr;
using std::vector;

using std::endl;
using std::make_unique;
using std::shared_ptr;
using sf::Vector2f;


class Button;
class Obj;
class Label;

class Gamew
{
public:
    Gamew();

    void Init(const std::wstring title = L"Gamew", const int Style = sf::Style::Close , const int width = 1200, const int height = 800);
    void Polling();
    void Update();
    bool getActive() { return isActive; }
    void Drawing();

private:

    void EventMouseMoved(sf::Event& event);
    void EventMouseButtonPressed(sf::Event& event);
    void EventMouseButtonReleased(sf::Event& event);
    void EventKeyPressed(sf::Event& event);

    bool isActive = true;
    sf::Event event;
    std::vector<std::shared_ptr<Obj>> ObjVector;
    sf::VertexArray V_A;
    sf::Font Geologica;
    std::shared_ptr<sf::RenderWindow> window;
    sf::Event::MouseMoveEvent mouse;
    sf::Texture texture;
    std::shared_ptr<Button> newButt;
    std::shared_ptr<Label> title;
    std::unique_ptr<DebugInfo> debugInfo;
};