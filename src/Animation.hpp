#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>

class Gamew;

class Animation {
  public:
    Animation();
    virtual ~Animation();

    Animation(Gamew *gamew, std::string path, int speed = 110, int offset = 32, bool infinity = 1);
    Animation& operator=(const Animation& o);
    virtual void SetOrigin();
    virtual void SetFlipped();
    virtual void Update();
    virtual void Stop();
    virtual void Draw();
    virtual void setPosition(sf::Vector2f pos);
    virtual void Start();
    bool DeleteIt() { return deleteIt; }
    bool getFlipped() { return flipped; };
    bool getAnimated() { return animate; };
    bool getStop() { return stop; }
    sf::Sprite sprite;
  
  protected:
    void Play();

    sf::Vector2f pos{};
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