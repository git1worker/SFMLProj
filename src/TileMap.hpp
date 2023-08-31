#pragma once
#include "Obj.hpp"
#include <SFML/Graphics.hpp>
#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"
#include <vector>
#include <map>
#include <memory>
#include "Tile.hpp"

#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

class Gamew;

class TileMap : public Obj
{
public:
    ~TileMap();
    TileMap(Gamew &gamew, std::string path);
    void Update(sf::Vector2f &offsetRelativeCenter) override;
    void Draw() override;
    void Zoom(int delta) override;
    bool assumeCollideX(const float x, sf::FloatRect &other) override;
    bool assumeCollideY(const float y, sf::FloatRect &other) override;

private:
    void FillMatrix(char *map);

    Gamew &gamew;
    std::map<int, std::unique_ptr<sf::Texture>> ids;
    std::string path;
    rapidxml::xml_document<> tileset, tilemap;
    Tile **map_Tiles;
    int heightInTiles, widthInTiles, heightTile, widthTile;
};