#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Bullet.hpp"
#include "gui/DebugInfo.hpp"
#include "gui/TextBox.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include "HandleEvent.hpp"
#include "../libs/ThreadPool/ThreadPool.h"
#include "Animation.hpp"
#include <list>


#define DEBUGINFO

#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

using sf::Vector2f;
using std::endl;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;

class Player;
class Button;
class AnimHuman;
class Obj;
class Label;
class Enemy;
class Gun;
class SplashOfBlood;
class Interface;


namespace Windows
{
    enum Windows
    {
        MainW,
        Game1,
        Game2,
        Game3,
        Game4,
    };
};

class Gamew
{
public:
    Gamew() = default;
    ~Gamew();
    void Init(const std::wstring title = L"Gamew", const int Style = sf::Style::Close, const int width = 1200, const int height = 800);
    void Polling();
    void Update();
    bool getActive() { return isActive; }
    void Drawing();
    void UpdateFps(float fps);

private:
    friend Player;
    friend TileMap;
    friend AnimHuman;
    friend HandleEvent;
    friend DebugInfo;
    friend Enemy;
    friend Gun;
    friend Bullet;
    friend Animation;
    friend SplashOfBlood;
    friend Interface;

    void HandleButton(Button *btn);
    void InitMainWindow();
    void InitWindow1();
    void InitWindow2();
    void InitWindow3();
    void InitWindow4();
    void CheckSwitchWindows();
    void CheckToDelete();

    std::list<std::list<std::unique_ptr<Obj>>::iterator> ObjToDelete;
    std::list<std::list<std::unique_ptr<Entity>>::iterator> EntitiesToDelete;
    std::list<std::list<std::unique_ptr<Bullet>>::iterator> BulletsToDelete;
    std::list<Animation*> AnimsToDelete;
    std::list<std::unique_ptr<Obj>> ObjVector;
    std::list<std::unique_ptr<Entity>> EntitiesVector;
    std::list<std::unique_ptr<Bullet>> BulletsVector;
    std::list<Animation*> AnimsVector;

    TextBox *selectedTextBox = nullptr;
    TileMap* currTileMap = nullptr;
    Player *player = nullptr;
    Interface* interface = nullptr;
    sf::Cursor cursorArrow, cursorText;
    bool cursorSetted = false;
    bool isActive = true;
    bool switchWindow = false;
    int currentWindow = Windows::MainW;
    bool TextBoxContains;

    ThreadPool pool{3};
    sf::Event event;
    HandleEvent handle = HandleEvent(this);
    sf::Font Geologica;
    std::unique_ptr<sf::RenderWindow> window;
    sf::View view;

    sf::Vector2f offsetRelativeCenter{};

    const float fps = 60;
    const float heightTile = 32;
    const float freeFall = 9.8;
    const float pxPerFrameFall = (freeFall * heightTile * (2.f / (fps * fps))) - (freeFall * heightTile * (1.f / (fps * fps)));
    int mouseX, mouseY;
    int screenOffsetX = 0, screenOffsetY = 0;
#ifdef DEBUGINFO
    std::unique_ptr<DebugInfo> debugInfo;
#endif // DEBUGINFO
};