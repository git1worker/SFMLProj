#include "TileMap.hpp"
#include <iostream>
#include <string>

using namespace rapidxml;

TileMap::TileMap(sf::RenderWindow *window, std::string path) : window(window), path(path)
{   
    file<> xmlFile(path.c_str());
    tilemap.parse<0>(xmlFile.data());
    while (path.back() != '/') path.pop_back();

    xml_node<>* root = tilemap.first_node();
    widthTile = atoi(root->first_attribute("tilewidth")->value());
    heightTile = atoi(root->first_attribute("tileheight")->value());
   
    file<> xmlFile2((path + std::string(root->first_node("tileset")->first_attribute("source")->value())).c_str());
    tileset.parse<0>(xmlFile2.data());
    xml_node<>* root2 = tileset.first_node();
    
    std::unique_ptr<sf::Texture> tmp;
    for (rapidxml::xml_node<> *tileNode = root2->first_node("tile"); tileNode; tileNode = tileNode->next_sibling())
    {   
        tmp = std::make_unique<sf::Texture>();
        tmp->loadFromFile(path + std::string(tileNode->first_node("image")->first_attribute("source")->value()));
        ids.emplace(atoi(tileNode->first_attribute("id")->value()), std::move(tmp)); 
    }
    
    char* map = root->first_node("layer")->first_node("data")->value();
    heightInTiles = atoi(root->first_node("layer")->first_attribute("height")->value());
    widthInTiles = atoi(root->first_node("layer")->first_attribute("width")->value());
    // Raw allocate a memory
    map_ids = new sf::Sprite*[heightInTiles];
    for (int i = 0; i < heightInTiles; ++i){
        map_ids[i] = new sf::Sprite[widthInTiles];
    }
    FillMatrix(map);
    movable = true;
    zoomable = true;
    
}

void TileMap::Update(int deltaX, int deltaY)
{   

    for (int i = 0; i < heightInTiles; ++i){
        for (int j = 0; j < widthInTiles; ++j){
            map_ids[i][j].setPosition(sf::Vector2f(map_ids[i][j].getPosition().x + deltaX, map_ids[i][j].getPosition().y + deltaY));
        }
    }
}

TileMap::~TileMap(){
    // Delete allocated memory
    for (int i = 0; i < heightInTiles; ++i)
        delete [] map_ids[i];
    delete [] map_ids;
}

void TileMap::Draw()
{   
    for (int i = 0; i < heightInTiles; ++i){
        for (int j = 0; j < widthInTiles; ++j){
            window->draw(map_ids[i][j]);
        }
    }
}

void TileMap::Zoom(int delta)
{
    
}

void TileMap::FillMatrix(char* map)
{   
    int posBuff = 0, posMatrix = 0;
    char buffer[10];

    for (int i = 0; map[i] != '\0'; ++i){
        if (map[i] == ',') {
            buffer[posBuff] = '\0';
            
            map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles] = sf::Sprite();
            if (atoi(buffer) != 0)
                map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles].setTexture(*(ids.at(atoi(buffer)-1)));
            
            map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles].setPosition(sf::Vector2f(widthTile * (posMatrix % widthInTiles), 
            heightTile * (posMatrix / widthInTiles)));
            ++posMatrix, posBuff = 0;
        }
        else if (map[i] >= '0' && map[i] <= '9'){
            buffer[posBuff++] = map[i];
        }
    }    
    // End condition
    buffer[posBuff] = '\0';
    map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles] = sf::Sprite();
    if (atoi(buffer) != 0)
        map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles].setTexture(*(ids.at(atoi(buffer)-1).get()));
    map_ids[posMatrix / widthInTiles][posMatrix % widthInTiles].setPosition(sf::Vector2f(widthTile * (posMatrix % widthInTiles), 
    heightTile * (posMatrix / widthInTiles)));
    
}
