#pragma once
#include <SFML/Graphics.hpp>

class Obj
{
public:
    Obj() = default;
    virtual void Draw() = 0;
    virtual void Update(){};
    virtual void Update(sf::Vector2f &offsetRelativeCenter){};
    virtual ~Obj() = default;
    virtual void Zoom(int delta){};
    bool isMovable() { return movable; }
    bool DeleteIt() { return deleteIt; }
    bool isZoomable() { return zoomable; }
    bool isCollidable() { return canCollide; }
    virtual bool collide(sf::FloatRect other){
        return posRect.intersects(other);
    }
    virtual bool assumeCollideX(const float x, sf::FloatRect &other){
        bool flag = false;
        posRect.left += x;
        if (posRect.intersects(other))
            flag = true;
        posRect.left -= x;
        return flag;
    }
    virtual bool assumeCollideY(const float y, sf::FloatRect &other){
        bool flag = false;
        posRect.top += y;
        if (posRect.intersects(other))
            flag = true;
        posRect.top -= y;
        return flag;
    }

    enum Names
    {
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
    sf::FloatRect posRect{};

protected:
    bool canCollide = false;
    bool zoomable = false;
    bool movable = false;
    bool deleteIt = false;
};