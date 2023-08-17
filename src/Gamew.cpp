#include "Gamew.hpp"
#include <iostream>
#include "Button.hpp"
#include <stdio.h>
#include "Label.hpp"


using std::cerr;
using std::cout;

Gamew::Gamew()
{
}

void Gamew::Init(const std::wstring title, const int Style, const int width, const int height)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, Style);
    window->setFramerateLimit(60);
    if (!Geologica.loadFromFile("../assets/fonts/Geologica.ttf"))
        cerr << "Failed to load font.\n", exit(1);
    if (!texture.loadFromFile("../assets/img/button.png"))
    {
        cerr << "Failed to load texture.\n", exit(1);
    }
    window->clear(sf::Color::White);

    //cout << window->getSize().x << endl;

    // Background
    V_A.setPrimitiveType(sf::Quads);
    V_A.append(sf::Vertex(Vector2f(0, 0), sf::Color(153, 153, 255)));
    V_A.append(sf::Vertex(Vector2f(0, window->getSize().y), sf::Color(0, 102, 204)));
    V_A.append(sf::Vertex(Vector2f(window->getSize().x, window->getSize().y), sf::Color(192, 192, 192)));
    V_A.append(sf::Vertex(Vector2f(window->getSize().x, 0), sf::Color(224, 224, 224)));

    //
    this->title = std::make_shared<Label>(window.get(), Geologica, L"Gamew", window->getSize().x / 2, window->getSize().y / 12, 60, 400);
    ObjVector.emplace_back(this->title);

    int numButtons = 4;
    float buttonWidth = 150.0f; // Ширина каждой кнопки
    float padding = (window->getSize().x - (numButtons * buttonWidth)) / (numButtons + 1); // Отступ между кнопками
    float currentX = padding;
    
    for (int i = 0; i < numButtons; ++i){
        if (i > 0) currentX += buttonWidth + padding;
        newButt = std::make_shared<Button>(window.get(), Geologica, currentX + 150/2, 200, std::wstring(std::wstring(L"Кнопка ") + std::to_wstring(i+1)));
        ObjVector.emplace_back(newButt);
    }
    this->debugInfo = make_unique<DebugInfo>(window.get(), Geologica, &event);
    
}

void Gamew::Polling()
{
    while (window->pollEvent(event))
    {   
        debugInfo->Update(&event);
        if (event.type == sf::Event::MouseMoved)
            EventMouseMoved(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            EventMouseButtonPressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            EventMouseButtonReleased(event);
        else if (event.type == sf::Event::KeyPressed)
            EventKeyPressed(event);
        else if (event.type == sf::Event::Closed)
            window->close(), isActive = false;
    }
}

void Gamew::Update()
{
    
}

void Gamew::Drawing()
{
    window->clear(sf::Color::White);
    window->draw(V_A);
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()))
            b->Draw();
        else if (auto *b = dynamic_cast<Label *>(i.get()))
            b->Draw();
    }
    debugInfo->Draw();
    window->display();
}

void Gamew::EventMouseMoved(sf::Event &event)
{   
    
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
        {
            b->SetHovered();
        }
        else if (b && b->isHovered() && !b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
            b->ResetHovered();
    }
}

void Gamew::EventMouseButtonPressed(sf::Event &event)
{
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
        {
            b->Click([&b]()
                     { b->ChangeText(L"Нажата"); });
        }
    }
}

void Gamew::EventMouseButtonReleased(sf::Event &event)
{
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getWasClicked())
        {
            b->Release();
        }
    }
}

void Gamew::EventKeyPressed(sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Escape)
        window->close(), isActive = false;
}
