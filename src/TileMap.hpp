#pragma once
#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"
#include "Obj.hpp"
#include "Tile.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>

#ifndef DEBUG
#define DEBUG                                                                                                                                        \
    { std::cout << "Line: " << __LINE__ << std::endl; }
#endif // DEBUG

class Gamew;
using namespace rapidxml;

class TileMap : public Obj {
  public:
    ~TileMap();
    TileMap(Gamew *gamew, std::string path);
    void Update() override;
    void Draw() override;
    bool collide(sf::FloatRect other) override;
    bool Intersection(const Section& a) override;
    bool assumeCollideX(const float x, sf::FloatRect other) override;
    bool assumeCollideY(const float y, sf::FloatRect other) override;
    bool collidePoint(sf::Vector2f p) override;
    bool IsThereLadNearby(sf::FloatRect &other);

  private:

    void FillMatrix();
    bool IsThisInsideWindow(const sf::FloatRect &posRect);
    void FillMatrixBackground();
    void OneTileProcessingBackground(int &posBuff, int &posMatrix, char *buffer);
    void OneTileProcessing(int &posBuff, int &posMatrix, char *buffer);
    void ParseMapToMatrix();

    Gamew *gamew;
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
    sf::Vector2f offsetRelativeCenter{};
    char *map2;
    char *map;
};