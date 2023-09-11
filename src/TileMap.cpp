#include "TileMap.hpp"
#include "Enemy.hpp"
#include "Gamew.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include "Debug.hpp"

void TileMap::ParseMapToMatrix() {
    file<> xmlFile(path.c_str());
    tilemap.parse<0>(xmlFile.data());
    while (path.back() != '/')
        path.pop_back();

    root = tilemap.first_node();
    widthTile = atoi(root->first_attribute("tilewidth")->value());
    heightTile = atoi(root->first_attribute("tileheight")->value());

    file<> xmlFile2((path + std::string(root->first_node("tileset")->first_attribute("source")->value())).c_str());
    tileset.parse<0>(xmlFile2.data());
    root2 = tileset.first_node();

    std::unique_ptr<sf::Texture> tmp;
    for (rapidxml::xml_node<> *tileNode = root2->first_node("tile"); tileNode; tileNode = tileNode->next_sibling()) {
        tmp = std::make_unique<sf::Texture>();
        tmp->loadFromFile(path + std::string(tileNode->first_node("image")->first_attribute("source")->value()));
        ids.emplace(atoi(tileNode->first_attribute("id")->value()), std::move(tmp));
    }
    for (rapidxml::xml_node<> *tileNode = root->first_node("layer"); tileNode; tileNode = tileNode->next_sibling()) {
        if (atoi(tileNode->first_attribute("id")->value()) == 1)
            map = tileNode->first_node("data")->value();
        else if (atoi(tileNode->first_attribute("id")->value()) == 3)
            map2 = tileNode->first_node("data")->value();
    }
    heightInTiles = atoi(root->first_node("layer")->first_attribute("height")->value());
    widthInTiles = atoi(root->first_node("layer")->first_attribute("width")->value());
    // Allocating of memory
    map_Tiles = new Tile *[heightInTiles];
    for (int i = 0; i < heightInTiles; ++i)
        map_Tiles[i] = new Tile[widthInTiles];
    map_TilesBackground = new Tile *[heightInTiles];
    for (int i = 0; i < heightInTiles; ++i)
        map_TilesBackground[i] = new Tile[widthInTiles];
    blackoutTile.setSize(sf::Vector2f(widthTile, heightTile));
    blackoutTile.setFillColor(sf::Color(0, 0, 0, 70));
    FillMatrix();
    FillMatrixBackground();
}

TileMap::TileMap(Gamew *gamew, std::string path) : gamew(gamew), path(path) {
    ParseMapToMatrix();

    canCollide = true;
    movable = true;
}

void TileMap::Update() {
    offsetRelativeCenter = gamew->offsetRelativeCenter;
}

TileMap::~TileMap() {
    // Delete allocated memory
    for (int i = 0; i < heightInTiles; ++i)
        delete[] map_Tiles[i];
    delete[] map_Tiles;
    for (int i = 0; i < heightInTiles; ++i)
        delete[] map_TilesBackground[i];
    delete[] map_TilesBackground;
}

void TileMap::Draw() {
    for (int i = 0; i < heightInTiles; ++i) {
        for (int j = 0; j < widthInTiles; ++j) {
            if (map_TilesBackground[i][j].id != -1 &&
                IsThisInsideWindow(map_TilesBackground[i][j].posRect)) {
                map_TilesBackground[i][j].sprite.setPosition(map_TilesBackground[i][j].posRect.left + offsetRelativeCenter.x, 
                    map_TilesBackground[i][j].posRect.top + offsetRelativeCenter.y);
                blackoutTile.setPosition(map_TilesBackground[i][j].sprite.getPosition().x, map_TilesBackground[i][j].sprite.getPosition().y);
                gamew->window->draw(map_TilesBackground[i][j].sprite);
                gamew->window->draw(blackoutTile);
            }
        }
    }
    for (int i = 0; i < heightInTiles; ++i) {
        for (int j = 0; j < widthInTiles; ++j) {
            if (map_Tiles[i][j].id != -1 &&
                IsThisInsideWindow(map_Tiles[i][j].posRect)) {
                    if (map_Tiles[i][j].id == 19)
                        map_Tiles[i][j].sprite.setPosition(
                            sf::Vector2f(map_Tiles[i][j].posRect.left + offsetRelativeCenter.x, map_Tiles[i][j].posRect.top - 24 + offsetRelativeCenter.y));
                    else 
                        map_Tiles[i][j].sprite.setPosition(
                            sf::Vector2f(map_Tiles[i][j].posRect.left + offsetRelativeCenter.x, map_Tiles[i][j].posRect.top + offsetRelativeCenter.y));
                    gamew->window->draw(map_Tiles[i][j].sprite);
                }

                
        }
    }
}

bool TileMap::collide(sf::FloatRect other) {

    int maxX = other.left + other.width + widthTile * 2;
    int maxY = other.top + other.height + heightTile * 2;
    int minX = other.left - widthTile * 2;
    int minY = other.top - heightTile * 2;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    bool flag = false;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            if (map_Tiles[i][j].canCollide && map_Tiles[i][j].posRect.intersects(other))
                flag = true;
        }
    }
    return flag;
}

bool TileMap::Intersection(const Section& a) { 
    bool flag = false;
    int maxX = a.x1 > a.x2 ? a.x1 + widthTile : a.x2 + widthTile;
    int maxY = a.y1 > a.y2 ? a.y1 + heightTile : a.y2 + heightTile;
    int minX = a.x1 < a.x2 ? a.x1 - widthTile: a.x2 - widthTile;
    int minY = a.y1 < a.y2 ? a.y1 - heightTile : a.y2 - heightTile;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    Section s1 {posRect.left, posRect.top, posRect.left + posRect.width, posRect.top + posRect.height};
    Section s2 {posRect.left + posRect.width, posRect.top, posRect.left, posRect.top + posRect.height};
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    //int cnt = 0;
    //Timer t;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            if (map_Tiles[i][j].canCollide) {
                s1.x1 = map_Tiles[i][j].posRect.left;
                s1.y1 = map_Tiles[i][j].posRect.top;
                s1.x2 = map_Tiles[i][j].posRect.left + map_Tiles[i][j].posRect.width;
                s1.y2 = map_Tiles[i][j].posRect.top + map_Tiles[i][j].posRect.height;

                s2.x1 = map_Tiles[i][j].posRect.left + map_Tiles[i][j].posRect.width;
                s2.y1 = map_Tiles[i][j].posRect.top;
                s2.x2 = map_Tiles[i][j].posRect.left;
                s2.y2 = map_Tiles[i][j].posRect.top + map_Tiles[i][j].posRect.height;
                
                if (intersectionSectionAndSection(s1, a) || 
                    intersectionSectionAndSection(s2, a))
                    flag = true;
                
            }
            //++cnt;
        }
    }
    // std::cout << "Done " << t.GetTime() << ' ' << cnt << ' ' <<
    // minY / heightTile << ' ' << ii << ' '
    // << minX / widthTile << ' ' << jj << '\n';
    return flag;
}

bool TileMap::assumeCollideY(const float y, sf::FloatRect other) {
    bool flag = false;
    int maxX = other.left + other.width + widthTile * 2;
    int maxY = other.top + other.height + heightTile * 2;
    int minX = other.left - widthTile * 2;
    int minY = other.top - heightTile * 2;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            other.top += y;
            if (map_Tiles[i][j].canCollide && map_Tiles[i][j].posRect.intersects(other)) {
                flag = true;
                if (map_Tiles[i][j].id == 19 || map_Tiles[i][j].id == 18)
                    gamew->player->HP -= 5;
            }
            other.top -= y;
        }
    }
    return flag;
}

bool TileMap::collidePoint(sf::Vector2f p) {
    bool flag = false;
    int maxX = p.x + widthTile * 2;
    int maxY = p.y + heightTile * 2;
    int minX = p.x - widthTile * 2;
    int minY = p.y - heightTile * 2;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            if (map_Tiles[i][j].canCollide && map_Tiles[i][j].posRect.contains(p)) {
                flag = true;
            }
        }
    }
    return flag;
}

bool TileMap::IsThereLadNearby(sf::FloatRect &other) {
    bool flag = false;
    int maxX = other.left + other.width + widthTile * 2;
    int maxY = other.top + other.height + heightTile * 2;
    int minX = other.left - widthTile * 2;
    int minY = other.top - heightTile * 2;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            if (map_Tiles[i][j].posRect.intersects(other) && map_Tiles[i][j].id == 14)
                flag = true;
        }
    }
    return flag;
}

bool TileMap::assumeCollideX(const float x, sf::FloatRect other) {
    int maxX = other.left + other.width + widthTile * 2;
    int maxY = other.top + other.height + heightTile * 2;
    int minX = other.left - widthTile * 2;
    int minY = other.top - heightTile * 2;
    if (minX < 0) minX = 0;
    if (minY < 0) minY = 0;
    if (maxX > widthTile * widthInTiles) maxX = widthTile * widthInTiles;
    if (maxY > heightTile * heightInTiles) maxY = heightTile * heightInTiles;
    int ii = maxY / heightTile;
    int jj = maxX / widthTile;
    bool flag = false;
    for (int i = minY / heightTile; i < ii && !flag; ++i) {
        for (int j = minX / widthTile; j < jj && !flag; ++j) {
            other.left += x;
            if (map_Tiles[i][j].canCollide && map_Tiles[i][j].posRect.intersects(other)) {
                auto t = map_Tiles[i][j];
                flag = true;
            }
            other.left -= x;
        }
    }
    return flag;
}

void TileMap::FillMatrix() {
    int posBuff = 0, posMatrix = 0;
    char buffer[10];

    for (int i = 0; map[i] != '\0'; ++i) {
        if (map[i] == ',') {
            OneTileProcessing(posBuff, posMatrix, buffer);
            ++posMatrix, posBuff = 0;
        } else if (map[i] >= '0' && map[i] <= '9')
            buffer[posBuff++] = map[i];
    }
    // Last tile
    OneTileProcessing(posBuff, posMatrix, buffer);
}

bool TileMap::IsThisInsideWindow(const sf::FloatRect &posRect) {
    if (posRect.left + posRect.width + gamew->offsetRelativeCenter.x < 0 || posRect.left + gamew->offsetRelativeCenter.x > gamew->window->getSize().x)
        return false;
    if (posRect.top + posRect.height + gamew->offsetRelativeCenter.y < 0 || posRect.top + gamew->offsetRelativeCenter.y > gamew->window->getSize().y)
        return false;
    return true;
}

void TileMap::FillMatrixBackground() {
    int posBuff = 0, posMatrix = 0;
    char buffer[4];

    for (int i = 0; map2[i] != '\0'; ++i) {
        if (map2[i] == ',') {
            OneTileProcessingBackground(posBuff, posMatrix, buffer);
            ++posMatrix, posBuff = 0;
        } else if (map2[i] >= '0' && map2[i] <= '9')
            buffer[posBuff++] = map2[i];
    }
    // Last tile
    OneTileProcessingBackground(posBuff, posMatrix, buffer);
}

void TileMap::OneTileProcessingBackground(int &posBuff, int &posMatrix, char *buffer) {
    buffer[posBuff] = '\0';
    int idInTiled = atoi(buffer) - 1;
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles] = Tile();
    if (idInTiled != -1) {
        map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setTexture(*(ids.at(idInTiled)));
        map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].id = idInTiled;
    } else
        map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].id = -1;
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setPosition(
        sf::Vector2f(widthTile * (posMatrix % widthInTiles), heightTile * (posMatrix / widthInTiles)));
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.left = widthTile * (posMatrix % widthInTiles);
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.top = heightTile * (posMatrix / widthInTiles);
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.width = widthTile;
    map_TilesBackground[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.height = heightTile;
}

void TileMap::OneTileProcessing(int &posBuff, int &posMatrix, char *buffer) {

    buffer[posBuff] = '\0';
    int idInTiled = atoi(buffer) - 1;
    if (idInTiled == 27) {
        gamew->EntitiesVector.emplace_back(
            std::make_unique<Enemy>(gamew, sf::Vector2f(widthTile * (posMatrix % widthInTiles), heightTile * (posMatrix / widthInTiles))));
    } else {
        map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles] = Tile();
        if (idInTiled != -1) {
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setTexture(*(ids.at(idInTiled)));
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].id = idInTiled;
            if (idInTiled != 13 && idInTiled != 14 && idInTiled != 0 && idInTiled != 1 && idInTiled != 11 && idInTiled != 12)
                map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].canCollide = true;
        }
        map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].sprite.setPosition(
            sf::Vector2f(widthTile * (posMatrix % widthInTiles), heightTile * (posMatrix / widthInTiles)));
        if (idInTiled == 19) {
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.left = widthTile * (posMatrix % widthInTiles);
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.top = heightTile * (posMatrix / widthInTiles) + 24;
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.width = widthTile;
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.height = heightTile - 24;
        } else {
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.left = widthTile * (posMatrix % widthInTiles);
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.top = heightTile * (posMatrix / widthInTiles);
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.width = widthTile;
            map_Tiles[posMatrix / widthInTiles][posMatrix % widthInTiles].posRect.height = heightTile;
        }
    }
}
