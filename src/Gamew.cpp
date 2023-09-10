#include "Gamew.hpp"
#include "Background.hpp"
#include "Debug.hpp"
#include "Player.hpp"
#include "gui/Button.hpp"
#include "gui/Interface.hpp"
#include "gui/Label.hpp"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <type_traits>

using std::cerr;
using std::cout;
using tp = std::chrono::system_clock::time_point;
using sc = std::chrono::system_clock;
using ms = std::chrono::milliseconds;

void Gamew::UpdateFps(float fps) {
#ifdef DEBUGINFO
    debugInfo->UpdateFps(fps);
#endif // DEBUGINFO
}

Gamew::~Gamew() {
    if (interface != nullptr)
        delete interface;
    AnimsVector.clear();
}

void Gamew::Init(const std::wstring title, const int Style, const int width, const int height) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, Style);
    //window->setPosition(sf::Vector2i(30, 30));
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(fps);
    if (!Geologica.loadFromFile("../assets/fonts/Geologica-Regular.ttf"))
        cerr << "Failed to load font.\n", exit(1);

    sf::Image icon;
    if (icon.loadFromFile("../assets/img/icon.png"))
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    InitMainWindow();
    if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow) || !cursorText.loadFromSystem(sf::Cursor::Text))
        cerr << "Failed to load cursor.\n", exit(1);

    window->setMouseCursor(cursorArrow);
#ifdef DEBUGINFO
    this->debugInfo = make_unique<DebugInfo>(this, &Geologica, &event);
    debugInfo->name = Element::DebugInfo;
#endif // DEBUGINFO
    view = window->getView();
    srand(time(NULL));
}

void Gamew::Polling() {
    while (window->pollEvent(event))
        handle(event);
}

void Gamew::HandleButton(Button *btn) {
    switch (btn->name) {
    case Element::butt1MainW:
        btn->Click([&]() {
            this->currentWindow = Windows::Game1;
            switchWindow = true;
        });
        break;
    case Element::butt2MainW:
        btn->Click([&]() {
            this->currentWindow = Windows::Game2;
            switchWindow = true;
        });
        break;
    case Element::butt3MainW:
        btn->Click([&]() {
            this->currentWindow = Windows::Game3;
            switchWindow = true;
        });
        break;
    case Element::butt4MainW:
        btn->Click([&]() {
            this->currentWindow = Windows::Game4;
            switchWindow = true;
        });
        break;
    case Element::butt1SelectionM:
        btn->Click([&]() {
            switchWindow = true;
        });
        break;
    case Element::butt2SelectionM:
        btn->Click([&]() {
            this->currentWindow = Windows::MainW;
            switchWindow = true;
        });
        break;
    case Element::butt3SelectionM:
        btn->Click([&]() {
            this->currentWindow = (1 + currentWindow) % 5;
            if (currentWindow == 0) ++currentWindow;
            switchWindow = true;
        });
        break;
    default:
        break;
    }
}

void Gamew::Update() {
    // Timer a;
    CheckSwitchWindows();
    auto updateObjectsTask = pool.enqueue([&] {
        for (std::list<std::unique_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it) {
            if ((*it)->isMovable())
                (*it)->Update(offsetRelativeCenter);
            else
                (*it)->Update();
            if ((*it)->DeleteIt())
                ObjToDelete.emplace_back(it);
        }
        for (std::list<std::unique_ptr<Entity>>::iterator it = EntitiesVector.begin(); it != EntitiesVector.end(); ++it) {
            (*it)->Update();
            if ((*it)->DeleteIt())
                EntitiesToDelete.emplace_back(it);
        }
        for (std::list<Animation *>::iterator it = AnimsVector.begin(); it != AnimsVector.end(); ++it) {
            if ((*it)->getStop())
                AnimsToDelete.emplace_back(*it);
            else
                (*it)->Update();
        }
        for (std::list<std::unique_ptr<Element>>::iterator it = ElementsVector.begin(); it != ElementsVector.end(); ++it) {
            (*it)->Update();
            if ((*it)->DeleteIt())
                ElementsToDelete.emplace_back(it);
        }
        if (player){
            if (!player->isDead()){
                if (interface)
                    interface->Update();
                if (EntitiesVector.size() == 1 && currentWindow != Windows::MainW){
                    
                }
            }
            else {
                --delay;
                if (delay < 0 && !selectionMenu){
                    // Black backgroung
                    selectionMenu = true;
                    auto t = make_unique<Background>(window.get(), &Geologica, sf::Color(0, 0, 0, 100));
                    ElementsVector.emplace_back(std::move(t));
                    // Buttons
                    int numButtons = 3;
                    float buttonWidth = 200.0f;                                                            // Ширина каждой кнопки
                    float padding = (window->getSize().x - (numButtons * buttonWidth)) / (numButtons + 1); // Отступ между кнопками
                    float currentX = padding;
                    for (int i = 0; i < numButtons; ++i) {
                        if (i > 0)
                            currentX += buttonWidth + padding;
                        auto b = std::make_unique<Button>(window.get(), &Geologica, currentX + 150 / 2, window->getSize().y / 3,
                                                        std::wstring(std::wstring(L"Кнопка") + std::to_wstring(i + 1)), buttonWidth);
                        b->getRect().setFillColor(sf::Color(b->getRect().getFillColor().r, b->getRect().getFillColor().g, b->getRect().getFillColor().b, 100));
                        if (i == 0){
                            b->name = Element::butt1SelectionM;
                            b->ChangeText(L"Заново");
                        }
                        else if (i == 1){
                            b->name = Element::butt2SelectionM;
                            b->ChangeText(L"Меню");
                        }
                        else if (i == 2){
                            b->name = Element::butt3SelectionM;
                            b->ChangeText(L"След. уровень");
                        }
                        ElementsVector.emplace_back(std::move(b));
                    }
                }
            }
        }
    }); 
    auto updateBulletsTask = pool.enqueue([&] {
        for (std::list<std::unique_ptr<Bullet>>::iterator it = BulletsVector.begin(); it != BulletsVector.end(); ++it) {
            (*it)->Update();
            if ((*it)->DeleteIt()) {
                BulletsToDelete.emplace_back(it);
            }
        }
    });
    updateObjectsTask.get();
    updateBulletsTask.get();
#ifdef DEBUGINFO
    debugInfo->Update();
#endif // DEBUGINFO

    CheckToDelete();

}

void Gamew::Drawing() {
    window->clear(sf::Color::White);

    // Drawing inside this ---
    for (std::list<std::unique_ptr<Obj>>::iterator it = ObjVector.begin(); it != ObjVector.end(); ++it)
        (*it)->Draw();
    for (std::list<std::unique_ptr<Entity>>::iterator it = EntitiesVector.begin(); it != EntitiesVector.end(); ++it)
        (*it)->Draw();
    for (std::list<std::unique_ptr<Bullet>>::iterator it = BulletsVector.begin(); it != BulletsVector.end(); ++it)
        (*it)->Draw();
    for (std::list<Animation *>::iterator it = AnimsVector.begin(); it != AnimsVector.end(); ++it)
        (*it)->Draw();
    if (interface)
        interface->Draw();
    for (std::list<std::unique_ptr<Element>>::iterator it = ElementsVector.begin(); it != ElementsVector.end(); ++it){
        (*it)->Draw();
    }
#ifdef DEBUGINFO
    debugInfo->Draw();
#endif // DEBUGINFO

    // -----------------------
    window->display();
}

void Gamew::InitMainWindow() {
    // Init
    currentWindow = Windows::MainW;
    // Background
    auto bg = std::make_unique<Background>(window.get(), &Geologica, true);
    bg->SetGradient(sf::Color(153, 153, 255), sf::Color(0, 102, 204), sf::Color(192, 192, 192), sf::Color(224, 224, 224));
    ObjVector.emplace_back(std::move(bg));
    // Title
    ElementsVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Gamew", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 60, 400));
    ElementsVector.back()->name = Element::titleMainW;
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
        if (i == 0)
            b->name = Element::butt1MainW;
        else if (i == 1)
            b->name = Element::butt2MainW;
        else if (i == 2)
            b->name = Element::butt3MainW;
        else if (i == 3)
            b->name = Element::butt4MainW;
        ElementsVector.emplace_back(std::move(b));
    }
    // TextBox
    ElementsVector.emplace_back(std::make_unique<TextBox>(window.get(), &Geologica, window->getSize().x / 2, window->getSize().y / 2, 30, 200, 3));
    ElementsVector.back()->name = Element::textBox1MainW;
}

void Gamew::InitWindow1() {
    // Init
    currentWindow = Windows::Game1;
    // Background
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background1.jpg");
    ObjVector.emplace_back(std::move(tmp1));
    // TileMap
    auto tmp4 = std::make_unique<TileMap>(*this, std::string("../assets/maps/map1.xml"));
    currTileMap = tmp4.get();
    ObjVector.emplace_back(std::move(tmp4));
    // Title that appears
    auto tmp2 = std::make_unique<Label>(window.get(), &Geologica, L"Уровень 1", window->getSize().x / 2, window->getSize().y / 12,
                                        Label::Align::Center, 55, 600);
    tmp2->name = Element::titleW1;
    tmp2->SetAnimation(Label::Anims::AppearanceDecay);
    ElementsVector.emplace_back(std::move(tmp2));
    // Player
    auto tmp3 = std::make_unique<Player>(*this, Player::Types::armoredAgent, sf::Vector2f(150, 150));
    player = tmp3.get();
    EntitiesVector.emplace_back(std::move(tmp3));

    interface = new Interface(this);
}

void Gamew::InitWindow2() {
    currentWindow = Windows::Game2;

    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background2.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ElementsVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 2", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ElementsVector.back()->name = Element::titleW2;
    currentWindow = Windows::Game2;
}

void Gamew::InitWindow3() {
    currentWindow = Windows::Game3;
    
    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background3.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ElementsVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 3", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ElementsVector.back()->name = Element::titleW3;
    currentWindow = Windows::Game3;
}

void Gamew::InitWindow4() {
    currentWindow = Windows::Game4;
    window->setView(window->getDefaultView());

    auto tmp1 = std::make_unique<Background>(window.get(), &Geologica);
    tmp1->SetTexture("../assets/img/background4.jpg");
    ObjVector.emplace_back(std::move(tmp1));

    ElementsVector.emplace_back(std::make_unique<Label>(window.get(), &Geologica, L"Уровень 4", window->getSize().x / 2, window->getSize().y / 12,
                                                   Label::Align::Center, 55, 600));
    ElementsVector.back()->name = Element::titleW4;
    currentWindow = Windows::Game4;
}

void Gamew::CheckSwitchWindows() {
    if (switchWindow) {
        ObjVector.clear();
        EntitiesVector.clear();
        BulletsVector.clear();
        AnimsVector.clear();
        ElementsVector.clear();
        if (interface != nullptr) {
            delete interface;
            interface = nullptr;
        }
        player = nullptr;
        currTileMap = nullptr;
        selectionMenu = false;
        window->setView(window->getDefaultView());

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
    for (const auto &i : ObjToDelete)
        ObjVector.erase(i);
    ObjToDelete.clear();
    for (const auto &i : EntitiesToDelete)
        EntitiesVector.erase(i);
    EntitiesToDelete.clear();
    for (const auto &i : BulletsToDelete)
        BulletsVector.erase(i);
    BulletsToDelete.clear();
    for (const auto &i : ElementsToDelete)
        ElementsVector.erase(i);
    ElementsToDelete.clear();
    for (const auto &i : AnimsToDelete)
        AnimsVector.remove(i);
    AnimsToDelete.clear();
}
