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
    ~Gamew() = default;
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

    ThreadPool pool{3};
    int currentWindow = Windows::MainW;
    bool isActive = true;
    bool switchWindow = false;
    sf::Event event;
    HandleEvent handle = HandleEvent(this);
    sf::Font Geologica;
    std::unique_ptr<sf::RenderWindow> window;
    TextBox *selectedTextBox = nullptr;
    sf::View view;
    bool cursorSetted = false;
    bool TextBoxContains;
    sf::Cursor cursorArrow, cursorText;
    int screenOffsetX = 0, screenOffsetY = 0;
    sf::Vector2f offsetRelativeCenter{};
    Player *player = nullptr;
    TileMap* currTileMap = nullptr;

    const float fps = 60;
    const float heightTile = 32;
    const float freeFall = 9.8;
    const float pxPerFrameFall = (freeFall * heightTile * (2.f / (fps * fps))) - (freeFall * heightTile * (1.f / (fps * fps)));

    int mouseX, mouseY;

#ifdef DEBUGINFO
    std::unique_ptr<DebugInfo> debugInfo;
#endif // DEBUGINFO
};