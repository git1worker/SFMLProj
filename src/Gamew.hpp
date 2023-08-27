#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "DebugInfo.hpp"
#include "TextBox.hpp"
#include "TileMap.hpp"
#include "Player.hpp"


#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

using std::unique_ptr;
using std::vector;

using std::endl;
using std::make_unique;
using std::shared_ptr;
using sf::Vector2f;

namespace Windows{
    enum Windows{
        MainW,
        Game1,
        Game2,
        Game3,
        Game4,
    };
};

class Button;
class Obj;
class Label;

class Gamew
{
public:
    Gamew();
    ~Gamew();
    void Init(const std::wstring title = L"Gamew", const int Style = sf::Style::Close , const int width = 1200, const int height = 800);
    void Polling();
    void Update();
    bool getActive() { return isActive; }
    void Drawing();
    void UpdateFps(float fps);

    

private:

    void EventMouseMoved(sf::Event& event);
    void EventMouseButtonPressed(sf::Event& event);
    void EventMouseButtonReleased(sf::Event& event);
    void EventKeyPressed(sf::Event& event);
    void EventMouseWheelScrolled(sf::Event& event);
    void HandleButton(Button * btn);
    void HandleTextBox();
    void HandleMovement(Obj* b);
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
    std::vector<std::unique_ptr<Obj>> ObjVector;
    std::vector<std::unique_ptr<Entity>> EntitiesVector;
    sf::Font Geologica;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<DebugInfo> debugInfo;
    TextBox* selectedTextBox = nullptr;
    sf::View view;
    bool cursorSetted = false;
    bool TextBoxContains;
    sf::Cursor cursorArrow, cursorText;
    int screenOffsetX = 0, screenOffsetY = 0;
    sf::Vector2f offsetRelativeCenter{};
};