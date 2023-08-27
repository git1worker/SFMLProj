#pragma once
#include <SFML/Graphics.hpp>

class Obj {
public:

    Obj();
    virtual void Draw() = 0;
    virtual void Update();
    virtual void Update(sf::Vector2f &offsetRelativeCenter);
    virtual ~Obj() = default;
    virtual void Zoom(int delta);
    bool isMovable() { return movable; }
    bool DeleteIt() { return deleteIt; }
    bool isZoomable() { return zoomable; }

    enum Names{
        None,
        DebugInfo,
        titleMainW,
        butt1MainW,
        butt2MainW,
        butt3MainW,
        butt4MainW,
        titleW1,
        titleW2,
        titleW3,
        titleW4,
        textBox1MainW,
        tileMapW1,
        backgroundW1,
        backgroundMW
    };

    Names name = None;

protected:
    
    bool zoomable = false;
    bool movable = false;
    bool deleteIt = false;
    float x, y, width, height;
};