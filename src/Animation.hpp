#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include "Entity.hpp"

class Gamew;

class Animation
{
public:
    Animation() = default;
    virtual ~Animation() = default;

    Animation(Gamew *gamew, std::string path, int speed = 110, int offset = 32, bool infinity = 1);

    virtual void SetOrigin();
    virtual void SetFlipped();
    virtual void Update();
    virtual void Stop();
    virtual void Draw();
    virtual void Start() { stop = false; currFrame = 1; animate = false; }
    bool DeleteIt() { return deleteIt; }
    bool getFlipped() { return flipped; };
    bool getAnimated() { return animate; };
    bool getStop() { return stop; }
    sf::Sprite sprite;

protected:
    void Play();

    bool deleteIt = false;
    sf::Texture tAnim;
    int speed, offset, numFrames;
    bool animate = false;
    std::chrono::system_clock::time_point start;
    int currFrame = 1;
    bool infinity = 1;
    bool stop = true;
    Gamew *gamew;
    bool flipped = false;
};