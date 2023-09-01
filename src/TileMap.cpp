#include "TileMap.hpp"
#include <iostream>
#include <string>
#include "Gamew.hpp"

using namespace rapidxml;

TileMap::TileMap(Gamew &gamew, std::string path) : gamew(gamew), path(path)
{
    file<> xmlFile(path.c_str());
    tilemap.parse<0>(xmlFile.data());
    while (path.back() != '/')
        path.pop_back();

    xml_node<> *root = tilemap.first_node();
    widthTile = atoi(root->first_attribute("tilewidth")->value());
    heightTile = atoi(root->first_attribute("tileheight")->value());

    file<> xmlFile2((path + std::string(root->first_node("tileset")->first_attribute("source")->value())).c_str());
    tileset.parse<0>(xmlFile2.data());
    xml_node<> *root2 = tileset.first_node();

    std::unique_ptr<sf::Texture> tmp;
    for (rapidxml::xml_node<> *tileNode = root2->first_node("tile"); tileNode; tileNode = tileNode->next_sibling())
    {
        tmp = std::make_unique<sf::Texture>();
        tmp->loadFromFile(path + std::string(tileNode->first_node("image")->first_attribute("source")->value()));
        ids.emplace(atoi(tileNode->first_attribute("id")->value()), std::move(tmp));
    }

    char *map = root->first_node("layer")->first_node("data")->value();
    heightInTiles = atoi(root->first_node("layer")->first_attribute("height")->value());
    widthInTiles = atoi(root->first_node("layer")->first_attribute("width")->value());
    // Raw allocate a memory
    map_Tiles = new Tile *[heightInTiles];
    for (int i = 0; i < heightInTiles; ++i)
    {
        map_Tiles[i] = new Tile[widthInTiles];
    }
    FillMatrix(map);

    canCollide = true;
    movable = true;
    zoomable = true;
}

void TileMap::Update(sf::Vector2f &offsetRelativeCenter)
{

    for (int i = 0; i < heightInTiles; ++i)
    {
        for (int j = 0; j < widthInTiles; ++j)
        {
            // if (widthTile * j + offsetRelativeCenter.x >= -2*widthTile && widthTile * j + offsetRelativeCenter.x <= gamew.window->getSize().x + 2*widthTile &&
            // heightTile * i + offsetRelativeCenter.y >= -2*heightTile && heightTile * i + offsetRelativeCenter.y <= gamew.window->getSize().y + 2*heightTile)
            map_Tiles[i][j].sprite.setPosition(sf::Vector2f(widthTile * j + offsetRelativeCenter.x, heightTile * i + offsetRelativeCenter.y));
            map_Tiles[i][j].posRect.left = widthTile * j + offsetRelativeCenter.x;
            map_Tiles[i][j].posRect.top = heightTile * i + offsetRelativeCenter.y;
        }
    }
}

TileMap::~TileMap()
{
    // Delete allocated memory
    for (int i = 0; i < heightInTiles; ++i)
        delete[] map_Tiles[i];
    delete[] map_Tiles;
}

void TileMap::Draw()
{
    for (int i = 0; i < heightInTiles; ++i)
    {
        for (int j = 0; j < widthInTiles; ++j)
        {
            if (map_Tiles[i][j].sprite.getPosition().x >= -2 * widthTile && map_Tiles[i][j].sprite.getPosition().x <= gamew.window->getSize().x + 2 * widthTile &&
                map_Tiles[i][j].sprite.getPosition().y >= -2 * heightTile && map_Tiles[i][j].sprite.getPosition().y <= gamew.window->getSize().y + 2 * heightTile)
                gamew.window->draw(map_Tiles[i][j].sprite);
        }
    }
}

void TileMap::Zoom(int delta)
{
}

bool TileMap::assumeCollideY(const float y, sf::FloatRect & other)
{
    bool flag = false;
    for (int i = 0; i < heightInTiles && !flag; ++i)
    {
        for (int j = 0; j < widthInTiles && !flag; ++j)
        {
            other.top += y;
            if (map_Tiles[i][j].posRect.intersects(other) && map_Tiles[i][j].canCollide)
                flag = true;
            other.top -= y;
        }
    }
    return flag;
}

bool TileMap::assumeCollideX(const float x, sf::FloatRect & other)
{   
    bool flag = false;
    for (int i = 0; i < heightInTiles && !flag; ++i)
    {
        for (int j = 0; j < widthInTiles && !flag; ++j)
        {
            other.left += x;
            if (map_Tiles[i][j].posRect.intersects(other) && map_Tiles[i][j].canCollide){
                auto t = map_Tiles[i][j];
                flag = true;
            }
                
            other.left -= x;
        }
    }
    return flag;
}

void TileMap::FillMatrix(char *map)
{
    int posBuff = 0, posMatrix = 0;
    char buffer[10];

    for (int i = 0; map[i] != '\0'; ++i)
    {
        if (map[i] == ',')
        {
            buffer[posBuff] = '\0';
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles] = Tile();
            if (atoi(buffer) != 0)
            {
                map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setTexture(*(ids.at(atoi(buffer) - 1)));
                map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].id = atoi(buffer) - 1;
                if (atoi(buffer) != 14 && atoi(buffer) != 15)
                    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].canCollide = true;
            }
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setPosition(sf::Vector2f(
                widthTile * (posMatrix % widthInTiles),
                heightTile * (posMatrix / widthInTiles)));
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.left = widthTile * (posMatrix % widthInTiles);
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.top = heightTile * (posMatrix / widthInTiles);
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.width = widthTile;
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.height = heightTile;
            ++posMatrix, posBuff = 0;
        }
        else if (map[i] >= '0' && map[i] <= '9')
        {
            buffer[posBuff++] = map[i];
        }
    }
    // Last tile
    buffer[posBuff] = '\0';
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles] = Tile();
    if (atoi(buffer) != 0)
    {
        map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setTexture(*(ids.at(atoi(buffer) - 1).get()));
        map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].id = atoi(buffer) - 1;
        map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].canCollide = true;
    }
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setPosition(sf::Vector2f(widthTile * (posMatrix % widthInTiles),
                                                                                                  heightTile * (posMatrix / widthInTiles)));
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.left = widthTile * (posMatrix % widthInTiles);
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.top = heightTile * (posMatrix / widthInTiles);
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.width = widthTile;
    map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.height = heightTile;
}
