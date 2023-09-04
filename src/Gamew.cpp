#include "Gamew.hpp"
#include "Background.hpp"
#include "Player.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <type_traits>

using std::cerr;
using std::cout;

void Gamew::UpdateFps(float fps) {
#ifdef DEBUGINFO
    debugInfo->UpdateFps(fps);
#endif // DEBUGINFO
}

void Gamew::Init(const std::wstring title, const int Style, const int width, const int height) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, Style);
    window->setFramerateLimit(fps);
    if (!Geologica.loadFromFile("../assets/fonts/Geologica-Regular.ttf"))
        cerr << "Failed to load font.\n", exit(1);

    sf::Image icon;
    if (icon.loadFromFile("../assets/img/icon.png")) {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    InitMainWindow();
    if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow) || !cursorText.loadFromSystem(sf::Cursor::Text)) {
        cerr << "Failed to load cursor.\n", exit(1);
    }
    window->setMouseCursor(cursorArrow);
#ifdef DEBUGINFO
    this->debugInfo = make_unique<DebugInfo>(this, &Geologica, &event);
    debugInfo->name = Obj::DebugInfo;
#endif // DEBUGINFO
    view = window->getView();
}

void Gamew::Polling() {
    while (window->pollEvent(event))
        handle(event);
}

void Gamew::HandleButton(Button *btn) {
    switch (btn->name) {
    case Button::butt1MainW:
        btn->Click([&]() {
            this->currentWindow = 1;
            switchWindow = true;
        });
        break;
    case Button::butt2MainW:
        btn->Click([&]() {
            this->currentWindow = 2;
            switchWindow = true;
        });
        break;
    case Button::butt3MainW:
        btn->Click([&]() {
            this->currentWindow = 3;
            switchWindow = true;
        });
        break;
    case Button::butt4MainW:
        btn->Click([&]() {
            this->currentWindow = 4;
            switchWindow = true;
        });
        break;
    default:
        break;
    }
}

void Gamew::Update() {
    CheckSwitchWindows();
    for (std::vector<std::unique_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it) {
        if ((*it)->isMovable())
            (*it)->Update(offsetRelativeCenter);
        else
            (*it)->Update();
        if ((*it)->DeleteIt())
            ObjToDelete.emplace_back(it);
    }
    for (std::vector<std::unique_ptr<Entity>>::iterator it = EntitiesVector.begin(); it != EntitiesVector.end(); ++it) {
        (*it)->Update();
        if ((*it)->DeleteIt())
            EntitiesToDelete.emplace_back(it);
    }
    for (std::vector<std::unique_ptr<Bullet>>::iterator it = BulletsVector.begin(); it != BulletsVector.end(); ++it){
        (*it)->Update();
        if ((*it)->DeleteIt()){
            BulletsToDelete.emplace_back(it);
            
        }
            
    }
      
    
    CheckToDelete();
#ifdef DEBUGINFO
    debugInfo->Update();
#endif // DEBUGINFO
}

void Gamew::Drawing() {
    window->clear(sf::Color::White);
    // Drawing inside this ---

    for (std::vector<std::unique_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it)
        (*it)->Draw();
    for (std::vector<std::unique_ptr<Entity>>::iterator it = EntitiesVector.begin(); it != EntitiesVector.end(); ++it)
        (*it)->Draw();
    for (std::vector<std::unique_ptr<Bullet>>::iterator it = BulletsVector.begin(); it != BulletsVector.end(); ++it)
        (*it)->Draw();
#ifdef DEBUGINFO
    debugInfo->Draw();
#endif // DEBUGINFO
    // -----------------------
    window->display();
}

void Gamew::InitMainWindow() {
    // Init
    player = nullptr;
    currentWindow = Windows::MainW;
    window->setView(window->getDefaultView());
    // Background
    auto bg = std::make_unique<Background>(window.get(), &Geologica, true);
    bg->SetGradient(sf::Color(153, 153, 255), sf::Color(0, 102, 204), sf::Color(192, 192, 192), sf::Color(224, 224, 224));
    bg->name = Obj::Names::backgroundMW;
    ObjVector.emplace_back(std::move(bg));
    // Title
    ObjVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Gamew", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 60, 400));
    ObjVector.back()->name = Obj::titleMainW;
    // Buttons
    int numButtons = 4;
    float buttonWidth = 150.0f;                                                            // Ширина каждой кнопки
    float padding = (window->getSize().x - (numButtons * buttonWidth)) / (numButtons + 1); // Отступ между кнопками
    float currentX = padding;
    for (int i = 0; i < numButtons; ++i) {
        if (i > 0)
            currentX += buttonWidth + padding;
        auto b = std::make_unique<Button>(window.get(), &Geologica, currentX + 150 / 2, 200,
                                          std::wstring(std::wstring(L"Уровень ") + std::to_wstring(i + 1)));

        b->getRect().setFillColor(sf::Color(b->getRect().getFillColor().r, b->getRect().getFillColor().g, b->getRect().getFillColor().b, 100));
        ObjVector.emplace_back(std::move(b));
    }
    ObjVector.at(2)->name = Obj::butt1MainW;
    ObjVector.at(3)->name = Obj::butt2MainW;
    ObjVector.at(4)->name = Obj::butt3MainW;
    ObjVector.at(5)->name = Obj::butt4MainW;
    // TextBox
    ObjVector.emplace_back(std::make_unique<TextBox>(window.get(), &Geologica, window->getSize().x / 2, window->getSize().y / 2, 30, 200, 3));
    ObjVector.back()->name = Obj::textBox1MainW;
}

void Gamew::InitWindow1() {
    // Init
    currentWindow = Windows::Game1;
    // Background
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background1.jpg");
    tmp1->name = Obj::Names::backgroundW1;
    ObjVector.emplace_back(std::move(tmp1));
    // TileMap
    auto tmp4 = std::make_unique<TileMap>(*this, std::string("../assets/maps/untitled.xml"));
    tmp4->name = Obj::Names::tileMapW1;
    currTileMap = tmp4.get();
    ObjVector.emplace_back(std::move(tmp4));
    // Title that appears
    auto tmp2 = std::make_unique<Label>(window.get(), &Geologica, L"Уровень 1", window->getSize().x / 2, window->getSize().y / 12,
                                        Label::Align::Center, 55, 600);
    tmp2->name = Obj::titleW1;
    tmp2->SetAnimation(Label::Anims::AppearanceDecay);
    ObjVector.emplace_back(std::move(tmp2));
    // Player
    auto tmp3 = std::make_unique<Player>(*this, Player::Types::armoredAgent, sf::Vector2f(150, 150));
    player = tmp3.get();
    EntitiesVector.emplace_back(std::move(tmp3));
}

void Gamew::InitWindow2() {
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background2.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ObjVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 2", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW2;
    currentWindow = Windows::Game2;
}

void Gamew::InitWindow3() {
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background3.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ObjVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 3", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW3;
    currentWindow = Windows::Game3;
}

void Gamew::InitWindow4() {
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background4.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ObjVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 4", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ObjVector.at(1)->name = Obj::titleW4;
    currentWindow = Windows::Game4;
}

void Gamew::CheckSwitchWindows() {
    if (switchWindow) {
        ObjVector.clear();
        EntitiesVector.clear();
        currTileMap = nullptr;

        switch (currentWindow) {
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

void Gamew::CheckToDelete() {
    for (const auto& i : ObjToDelete)
        ObjVector.erase(i);
    ObjToDelete.clear();
    for (const auto& i : EntitiesToDelete)
        EntitiesVector.erase(i);
    EntitiesToDelete.clear();
    for (const auto& i : BulletsToDelete)
        BulletsVector.erase(i);
    BulletsToDelete.clear();
}
