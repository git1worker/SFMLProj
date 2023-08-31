#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include "Gamew.hpp"

class Animation
{
public:
    Animation() = default;
    ~Animation() = default;

    Animation(Gamew *gamew, std::string path, int speed = 100, int offset = 32);

    void PlayOrigin();
    void PlayFlipped();
    void Stop();
    bool getFlipped();
    bool getAnimated();
    sf::Sprite sprite;

private:
    void Play();

    sf::Texture tAnim;
    int speed, offset, numFrames;
    bool animate = false;
    std::chrono::system_clock::time_point start;
    int currFrame = 1;
    Gamew *gamew;
    bool flipped = false;
};