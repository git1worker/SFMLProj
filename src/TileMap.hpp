#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"

class TileMap : Obj{
public:

    TileMap(sf::RenderWindow *window, std::string path);
    void Update() override;
    void Draw() override;

private:
    sf::RenderWindow *window;
    std::string path;
    rapidxml::file<> tileset, tilemap;
    
}