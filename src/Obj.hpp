#pragma once
#include <SFML/Graphics.hpp>
#include "Section.hpp"

class Obj {
  public:
    Obj() = default;
    virtual void Draw() = 0;
    virtual void Update(){};
    virtual void Update(const sf::Vector2f &offsetRelativeCenter){};
    virtual ~Obj() = default;

    virtual bool Intersection(Section a);
    bool isMovable() { return movable; }
    bool DeleteIt() { return deleteIt; }
    bool isCollidable() { return canCollide; }
    virtual bool collide(sf::FloatRect other) { return posRect.intersects(other); }
    virtual bool collidePoint(sf::Vector2f p) { return posRect.contains(p); }
    bool isPointOnTheSection(sf::Vector2f point, Section sect);
    bool intersectionSectionAndSection(const Section sect1, const Section sect2);
    virtual bool assumeCollideX(const float x, sf::FloatRect other);
    virtual bool assumeCollideY(const float y, sf::FloatRect other);

    enum Names {
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
    bool movable = false;
    bool deleteIt = false;
};