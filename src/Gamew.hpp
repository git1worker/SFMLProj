#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "gui/DebugInfo.hpp"
#include "gui/TextBox.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include "HandleEvent.hpp"

class Player;
class Animation;
class Button;
class Obj;
class Label;

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
    friend Animation;
    friend HandleEvent;

    void HandleButton(Button *btn);
    void InitMainWindow();
    void InitWindow1();
    void InitWindow2();
    void InitWindow3();
    void InitWindow4();
    void CheckSwitchWindows();
    void CheckToDelete();

    vector<std::vector<std::unique_ptr<Obj>>::iterator> ObjToDelete;
    vector<std::vector<std::unique_ptr<Entity>>::iterator> EntitiesToDelete;
    int currentWindow = Windows::MainW;
    bool isActive = true;
    bool switchWindow = false;
    sf::Event event;
    HandleEvent handle = HandleEvent(this);
    std::vector<std::unique_ptr<Obj>> ObjVector;
    std::vector<std::unique_ptr<Entity>> EntitiesVector;
    sf::Font Geologica;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<DebugInfo> debugInfo;
    TextBox *selectedTextBox = nullptr;
    sf::View view;
    bool cursorSetted = false;
    bool TextBoxContains;
    sf::Cursor cursorArrow, cursorText;
    int screenOffsetX = 0, screenOffsetY = 0;
    sf::Vector2f offsetRelativeCenter{};
    Player *player = nullptr;

    const int fps = 60;
    const int heightTile = 32;
    const float freeFall = 9.8;
    const float pxPerFrame = (freeFall * heightTile) / fps;
};