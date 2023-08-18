#include "Gamew.hpp"
#include <iostream>
#include "Button.hpp"
#include <stdio.h>
#include "Label.hpp"
#include "Background.hpp"

using std::cerr;
using std::cout;

Gamew::Gamew()
{
}

void Gamew::UpdateFps(float fps)
{
    debugInfo->UpdateFps(fps);
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
    sf::Image icon;
    if (icon.loadFromFile("../assets/img/icon.png"))
    {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    InitMainWindow();

    this->debugInfo = make_unique<DebugInfo>(window.get(), Geologica, &event);
    debugInfo->name = Obj::DebugInfo;
}

void Gamew::Polling()
{
    while (window->pollEvent(event))
    {
        debugInfo->UpdateEvents(&event);
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
    CheckSwitch();
    for (const auto &i : ObjVector)
    {
        i->Update();
    }
    debugInfo->Update();
}

void Gamew::Drawing()
{
    window->clear(sf::Color::White);
    for (const auto &i : ObjVector)
        i->Draw();

    // cout << fps << endl;
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
            HandleButton(b);
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
    if (event.key.code == sf::Keyboard::Escape){
        if (!switchWindow && currentWindow == 0)
            window->close(), isActive = false;
        else if (!switchWindow && currentWindow != Windows::MainW)
            switchWindow = true, currentWindow = 0;
    }
}

void Gamew::HandleButton(Button *btn)
{
    switch (btn->name)
    {
    case Button::butt1MainW:
        btn->Click([&]()
                   {
            this->currentWindow = 1;
            switchWindow = true; });
        break;
    case Button::butt2MainW:
        btn->Click([&]()
                   {
            this->currentWindow = 2;
            switchWindow = true; });
        break;
    case Button::butt3MainW:
        btn->Click([&]()
                   {
            this->currentWindow = 3;
            switchWindow = true; });
        break;
    case Button::butt4MainW:
        btn->Click([&]()
                   {
            this->currentWindow = 4;
            switchWindow = true; });
        break;
    default:
        break;
    }
}

void Gamew::InitMainWindow()
{
    // Background
    auto bg = std::make_shared<Background>(window.get(), Geologica);
    bg->SetGradient(sf::Color(153, 153, 255), sf::Color(0, 102, 204), sf::Color(192, 192, 192), sf::Color(224, 224, 224));
    ObjVector.emplace_back(bg);

    // Title
    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Gamew", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 60, 400));
    ObjVector.at(1)->name = Obj::titleMainW;
    // Buttons
    int numButtons = 4;
    float buttonWidth = 150.0f;                                                            // Ширина каждой кнопки
    float padding = (window->getSize().x - (numButtons * buttonWidth)) / (numButtons + 1); // Отступ между кнопками
    float currentX = padding;
    for (int i = 0; i < numButtons; ++i)
    {
        if (i > 0)
            currentX += buttonWidth + padding;
        auto b = std::make_shared<Button>(window.get(), Geologica, currentX + 150 / 2, 200, std::wstring(std::wstring(L"Игра ") + std::to_wstring(i + 1)));
        ObjVector.emplace_back(b);
        b->getRect().setFillColor(sf::Color(b->getRect().getFillColor().r, b->getRect().getFillColor().g, b->getRect().getFillColor().b, 100));
    }
    ObjVector.at(2)->name = Obj::butt1MainW;
    ObjVector.at(3)->name = Obj::butt2MainW;
    ObjVector.at(4)->name = Obj::butt3MainW;
    ObjVector.at(5)->name = Obj::butt4MainW;
    currentWindow = Windows::MainW;
}

void Gamew::InitWindow1()
{
    auto bg = std::make_shared<Background>(window.get(), Geologica);
    bg->SetStatic(sf::Color::White);
    ObjVector.emplace_back(bg);

    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 1", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 60, 400));
    ObjVector.at(1)->name = Obj::titleW1;
    
    currentWindow = Windows::Game1;
}

void Gamew::InitWindow2()
{
    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 2", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 60, 400));
    ObjVector.at(0)->name = Obj::titleW2;
    currentWindow = Windows::Game2;
}

void Gamew::InitWindow3()
{
    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 3", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 60, 400));
    ObjVector.at(0)->name = Obj::titleW3;
    currentWindow = Windows::Game3;
}

void Gamew::InitWindow4()
{
    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 4", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 60, 400));
    ObjVector.at(0)->name = Obj::titleW4;
    currentWindow = Windows::Game4;
}

void Gamew::CheckSwitch()
{
    if (switchWindow)
    {
        ObjVector.clear();
        switch (currentWindow)
        {
        case Windows::MainW:
            InitMainWindow();
            break;
        case Windows::Game1:
            InitWindow1();
            break;
        case Windows::Game2:
            InitWindow2();
            break;
        case Windows::Game3:
            InitWindow3();
            break;
        case Windows::Game4:
            InitWindow4();
            break;
        default:
            break;
        }
        switchWindow = false;
    }
}
