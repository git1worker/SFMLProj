#include "Gamew.hpp"
#include "Gun.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using tp = std::chrono::system_clock::time_point;
using sc = std::chrono::system_clock;

int main() {
    std::unique_ptr<Gamew> MyGame = std::make_unique<Gamew>();
    sf::Clock clock;
    sf::Time elapsedTime;
    float fps;
    tp start = std::chrono::system_clock::now();
    tp debug, debug2;
    MyGame->Init(L"Gamew");
    while (MyGame->getActive()) {
        elapsedTime = clock.restart();
        fps = 1.f / elapsedTime.asSeconds();
        // debug = std::chrono::system_clock::now();
        if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(500)) {
            start = std::chrono::system_clock::now();
            MyGame->UpdateFps(fps);
        }
        MyGame->Polling();
        MyGame->Update();
        // debug2 = std::chrono::system_clock::now();
        // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(debug2 - debug) << ' ';
        MyGame->Drawing();
        // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - debug2) << '\n';
        // sf::sleep(sf::seconds(1));
    }

    return 0;
}
