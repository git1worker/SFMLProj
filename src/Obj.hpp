#pragma once
#include <SFML/Graphics.hpp>

class Obj {
public:

    Obj() = default;
    virtual void Draw() = 0;
    virtual void Update() {};
    virtual void Update(sf::Vector2f &offsetRelativeCenter) {};
    virtual ~Obj() = default;
    virtual void Zoom(int delta) {};
    bool isMovable() { return movable; }
    bool DeleteIt() { return deleteIt; }
    bool isZoomable() { return zoomable; }
    virtual bool assumeCollide(sf::Vector2f deltaAssumedOffset, sf::IntRect& other) { 
        auto tmp = posRect;
        tmp.left += deltaAssumedOffset.x;
        tmp.top += deltaAssumedOffset.y;
        return tmp.intersects(other);
    }

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
    sf::IntRect posRect{};

protected:
    
    bool zoomable = false;
    bool movable = false;
    bool deleteIt = false;
    
};