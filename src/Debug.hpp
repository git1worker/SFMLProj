#pragma once
#include "Gamew.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

static int DebugCnt = 0;

using tp = std::chrono::system_clock::time_point;
using sc = std::chrono::system_clock;

#ifndef RTDrawing
#define RTDrawing(window, sprite)                                                                                                                    \
    {                                                                                                                                                \
        window->draw(sprite);                                                                                                                        \
        window->display();                                                                                                                           \
        std::cout << "Line: " << __LINE__ << '\t' << "File: " << __FILE__ << std::endl                                                               \
                  << "Cnt: " << DebugCnt++ << " Sprite pos: x = " << sprite.getPosition().x << " y = " << sprite.getPosition().y << std::endl;       \
        sf::sleep(sf::seconds(3));                                                                                                                   \
    }
#endif // RTDrawing

template <typename T> void Do(T v);

void Print();

template <typename Head, typename... Tail> void Print(Head h, Tail... t);

class Timer {
  public:
    Timer();
    std::chrono::microseconds GetTime();
    ~Timer();

  private:
    tp start;
};
