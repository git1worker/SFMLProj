#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"
#include <vector>
#include <map>
#include <memory>

#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

class TileMap : public Obj{
public:
    ~TileMap();
    TileMap(sf::RenderWindow *window, std::string path);
    void Update(sf::Vector2f &offsetRelativeCenter) override;
    void Draw() override;
    void Zoom(int delta) override;

private:

    void FillMatrix(char* map);

    
    std::map<int, std::unique_ptr<sf::Texture>> ids;
    sf::RenderWindow *window;
    std::string path;
    rapidxml::xml_document<> tileset, tilemap;
    sf::Sprite** map_ids;
    int heightInTiles, widthInTiles, heightTile, widthTile;
    
};