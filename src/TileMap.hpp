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
using namespace rapidxml;

class TileMap : public Obj
{
public:
    ~TileMap();
    TileMap(Gamew &gamew, std::string path);
    void Update(sf::Vector2f &offsetRelativeCenter) override;
    void Draw() override;
    void Zoom(int delta) override;
    bool collide(sf::FloatRect other) override;
    bool assumeCollideX(const float x, sf::FloatRect &other) override;
    bool assumeCollideY(const float y, sf::FloatRect &other) override;
    bool IsThereLadNearby(sf::FloatRect &other);

private:
    void FillMatrix();
    bool IsThisInsideWindow(const sf::FloatRect& posRect);
    void FillMatrixBackground();
    void OneTileProcessingBackground(int& posBuff, int &posMatrix, char* buffer);
    void OneTileProcessing(int& posBuff, int &posMatrix, char* buffer);
    void ParseMapToMatrix();

    Gamew &gamew;
    std::map<int, std::unique_ptr<sf::Texture>> ids;
    std::string path;
    rapidxml::xml_document<> tileset, tilemap;
    Tile **map_Tiles;
    Tile **map_TilesBackground;
    int heightInTiles, widthInTiles, heightTile, widthTile;
    sf::RectangleShape blackoutTile;
    // For parsing
    xml_node<> *root;
    xml_node<> *root2;
    char* map2;
    char *map;
};