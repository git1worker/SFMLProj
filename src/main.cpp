#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gamew.hpp"
#include "Button.hpp"
#include <vector>
#include <memory>

using std::cerr;
using std::cout;
using std::endl;

int main()
{
    std::unique_ptr<Gamew> MyGame = std::make_unique<Gamew>(Gamew());

    MyGame->Init();
    while (MyGame->getActive())
    {
        MyGame->Polling();
        MyGame->Update();
        MyGame->Drawing();
    }
    return 0;
}