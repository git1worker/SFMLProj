#pragma once
#include <iostream>
#include "Gamew.hpp"
#include <SFML/Graphics.hpp>

static int DebugCnt = 0;

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


