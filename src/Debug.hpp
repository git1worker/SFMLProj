#pragma once
#include <iostream>
#include "Gamew.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

static int DebugCnt = 0;

using tp = std::chrono::system_clock::time_point;
using sc = std::chrono::system_clock;

#ifndef RTDrawing
#define RTDrawing(window, sprite)                         \
    {                                                     \
        window->draw(sprite);                             \
        window->display();                                \
        std::cout << "Line:\t" << __LINE__ << std::endl   \
                  << "File:\t" << __FILE__ << std::endl   \
                  << "Cnt:\t" << DebugCnt++ << std::endl; \
        sf::sleep(sf::seconds(3));                        \
    }
#endif // RTDrawing

template <typename T>
void Do(T v);

void Print();

template <typename Head, typename... Tail>
void Print(Head h, Tail... t);

class Timer {
public:
    Timer();
    ~Timer();

private:
    tp start;
};
