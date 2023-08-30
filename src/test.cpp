#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

class Base{
public:
    virtual void foo() = 0;
};

class MyClass : public Base{
public:
    static int num;

    void foo(){
        std::cout << num++ << std::endl; 
    };

};

int MyClass::num {};

int main(){

    // std::vector<std::shared_ptr<Base>> v;
    // for (int i = 0; i < 5; ++i){
    //     v.emplace_back(std::make_shared<MyClass>());
    // }

    // for (auto& i : v){
    //     i->foo();
    // }

    // unsigned int c = 10;
    // float a = 1.11;
    // std::cout << a + c << std::endl;
    // std::string path("../assets/maps/untitled.xml");
    // file<> xmlFile(path.c_str());
    // rapidxml::xml_document<> tilemap;
    // tilemap.parse<0>(xmlFile.data());
    // while (path.back() != '/') path.pop_back();

    // xml_node<>* root = tilemap.first_node();
    // std::cout << root->name() << "\n";
    // file<> xmlFile2((path + std::string(root->first_node("tileset")->first_attribute("source")->value())).c_str());
    // rapidxml::xml_document<> tileset;
    // tileset.parse<0>(xmlFile2.data());
    // xml_node<>* root2 = tileset.first_node();
    // std::cout << root2->name() << "\n";
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(500, 500), "test");
    sf::Texture tmp;
    tmp.loadFromFile("../assets/img/characters/anims_gray_agent.png");
    sf::Sprite a(tmp);
    auto t = a.getTextureRect();
    t.width = -t.width;
    t.left = t.left + abs(t.width);
    a.setTextureRect(t);
    
    window.clear(sf::Color(255,255,255));
    window.draw(a);
    window.display();
    sf::sleep(sf::seconds(10));
    t = a.getTextureRect();
    t.width = -t.width;
    t.left = t.left - abs(t.width);
    a.setTextureRect(t);
    
    window.clear(sf::Color(255,255,255));
    window.draw(a);
    window.display();
    sf::sleep(sf::seconds(10));
    return 0;
}