#include "Gamew.hpp"
#include <iostream>
#include "Button.hpp"
#include <stdio.h>
#include "Label.hpp"
#include "Background.hpp"
#include <string.h>

using std::cerr;
using std::cout;

Gamew::Gamew()
{
}

Gamew::~Gamew()
{
}

void Gamew::UpdateFps(float fps) { debugInfo->UpdateFps(fps); }

void Gamew::Init(const std::wstring title, const int Style, const int width, const int height)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title, Style);
    window->setFramerateLimit(60);
    if (!Geologica.loadFromFile("../assets/fonts/Geologica-Regular.ttf"))
        cerr << "Failed to load font.\n", exit(1);

    sf::Image icon;
    if (icon.loadFromFile("../assets/img/icon.png"))
    {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    InitMainWindow();
    if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow) || !cursorText.loadFromSystem(sf::Cursor::Text))
    {
        cerr << "Failed to load cursor.\n", exit(1);
    }
    window->setMouseCursor(cursorArrow);

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

void Gamew::EventMouseMoved(sf::Event &event)
{
    TextBoxContains = false;
    for (const auto &i : ObjVector)
    {

        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
        {
            b->SetHovered();
        }
        else if (b && b->isHovered() && !b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
            b->ResetHovered();
        if (auto *b = dynamic_cast<TextBox *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
        {
            if (!cursorSetted)
            {
                window->setMouseCursor(cursorText);
                cursorSetted = true;
            }
            TextBoxContains = true;
        }
    }
    if (cursorSetted && !TextBoxContains)
    {
        window->setMouseCursor(cursorArrow);
        cursorSetted = false;
    }
}

void Gamew::EventMouseButtonPressed(sf::Event &event)
{
    selectedTextBox = nullptr;
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
            HandleButton(b);
        
        else if (auto *b = dynamic_cast<TextBox *>(i.get()); b && b->getRect().getGlobalBounds().contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
            selectedTextBox = b;
        
    }
}

void Gamew::EventMouseButtonReleased(sf::Event &event)
{
    for (const auto &i : ObjVector)
    {
        if (auto *b = dynamic_cast<Button *>(i.get()); b && b->getWasClicked())
            b->Release();
        
    }
}

void Gamew::EventKeyPressed(sf::Event &event)
{

    if (event.key.code == sf::Keyboard::Escape)
    {
        if (!switchWindow && currentWindow == 0)
            window->close(), isActive = false;
        else if (!switchWindow && currentWindow != Windows::MainW)
            switchWindow = true, currentWindow = 0;
    }
    else if (selectedTextBox != nullptr)
        HandleTextBox();
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

void Gamew::HandleTextBox()
{
    if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z)
    {
        if (event.key.shift)
            selectedTextBox->AppendLetter((wchar_t)(L'A' + event.key.code));
        else
            selectedTextBox->AppendLetter((wchar_t)(L'a' + event.key.code));
    }
    else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9)
    {
        selectedTextBox->AppendLetter((wchar_t)(L'0' + event.key.code - sf::Keyboard::Num0));
    }
    else if (event.key.code == sf::Keyboard::Space)
    {
        selectedTextBox->AppendLetter(L' ');
    }
    else if (event.key.code == sf::Keyboard::SemiColon)
    {
        selectedTextBox->AppendLetter(L';');
    }
    else if (event.key.code == sf::Keyboard::Quote)
    {
        selectedTextBox->AppendLetter(L'\'');
    }
    else if (event.key.code == sf::Keyboard::Comma)
    {
        selectedTextBox->AppendLetter(L',');
    }
    else if (event.key.code == sf::Keyboard::Period)
    {
        selectedTextBox->AppendLetter(L'.');
    }
    else if (event.key.code == sf::Keyboard::Slash)
    {
        selectedTextBox->AppendLetter(L'/');
    }
    else if (event.key.code == sf::Keyboard::BackSpace)
    {
        selectedTextBox->DelLetter();
    }
}

void Gamew::Update()
{
    CheckSwitchWindows();
    for (std::vector<std::shared_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it)
    {
        if (auto *b = dynamic_cast<TextBox *>((*it).get())){
            if (b == selectedTextBox)
                b->Update();
        } 
        else
        {
            (*it)->Update();
        }
        if ((*it)->DeleteIt())
            ObjToDelete.emplace_back(it);
    }
    CheckObjToDelete();
    debugInfo->Update();
}

void Gamew::Drawing()
{
    window->clear(sf::Color::White);
    for (std::vector<std::shared_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it)
        (*it)->Draw();

    // cout << fps << endl;
    debugInfo->Draw();
    window->display();
}

void Gamew::InitMainWindow()
{
    currentWindow = Windows::MainW;
    // Background
    auto bg = std::make_shared<Background>(window.get(), Geologica, true);
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
        auto b = std::make_shared<Button>(window.get(), Geologica, currentX + 150 / 2, 200, std::wstring(std::wstring(L"Уровень ") + std::to_wstring(i + 1)));
        ObjVector.emplace_back(b);
        b->getRect().setFillColor(sf::Color(b->getRect().getFillColor().r, b->getRect().getFillColor().g, b->getRect().getFillColor().b, 100));
    }
    ObjVector.at(2)->name = Obj::butt1MainW;
    ObjVector.at(3)->name = Obj::butt2MainW;
    ObjVector.at(4)->name = Obj::butt3MainW;
    ObjVector.at(5)->name = Obj::butt4MainW;

    // TextBox
    ObjVector.emplace_back(std::make_shared<TextBox>(window.get(), Geologica, window->getSize().x / 2, window->getSize().y / 2, 30, 200, 3));
    ObjVector.at(6)->name = Obj::textBox1MainW;
}

void Gamew::InitWindow1()
{
    auto tmp1 = std::make_shared<Background>(window.get(), Geologica);
    tmp1->SetTexture("../assets/img/background1.jpg");
    ObjVector.emplace_back(tmp1);

    auto tmp2 = std::make_shared<Label>(window.get(), Geologica, L"Уровень 1", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 55, 600);
    ObjVector.emplace_back(tmp2);
    tmp2->name = Obj::titleW1;
    tmp2->SetAnimation(Label::Anims::AppearanceDecay);

    currentWindow = Windows::Game1;
}

void Gamew::InitWindow2()
{
    auto tmp1 = std::make_shared<Background>(window.get(), Geologica);
    tmp1->SetTexture("../assets/img/background2.jpg");
    ObjVector.emplace_back(tmp1);

    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 2", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW2;
    currentWindow = Windows::Game2;
}

void Gamew::InitWindow3()
{   
    auto tmp1 = std::make_shared<Background>(window.get(), Geologica);
    tmp1->SetTexture("../assets/img/background3.jpg");
    ObjVector.emplace_back(tmp1);

    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 3", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW3;
    currentWindow = Windows::Game3;
}

void Gamew::InitWindow4()
{   
    auto tmp1 = std::make_shared<Background>(window.get(), Geologica);
    tmp1->SetTexture("../assets/img/background4.jpg");
    ObjVector.emplace_back(tmp1);

    ObjVector.emplace_back(std::make_shared<Label>(window.get(), Geologica, L"Уровень 4", window->getSize().x / 2, window->getSize().y / 12, Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW4;
    currentWindow = Windows::Game4;
}

void Gamew::CheckSwitchWindows()
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

void Gamew::CheckObjToDelete()
{
    for (const auto i : ObjToDelete)
        ObjVector.erase(i);
    ObjToDelete.clear();
}
