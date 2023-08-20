#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamew.hpp"
#include "Button.hpp"
#include <vector>
#include <memory>
#include <chrono>

using std::cerr;
using std::cout;
using std::endl;

int main()
{
    std::unique_ptr<Gamew> MyGame = std::make_unique<Gamew>();
    sf::Clock clock;
    sf::Time elapsedTime;
    float fps;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    MyGame->Init();
    while (MyGame->getActive())
    {   
        elapsedTime = clock.restart();
        fps = 1.f / elapsedTime.asSeconds();
        if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(500)){
            start = std::chrono::system_clock::now();
            MyGame->UpdateFps(fps);
        }
        MyGame->Polling();
        MyGame->Update();
        MyGame->Drawing();
        
            
    }
    return 0;
}
