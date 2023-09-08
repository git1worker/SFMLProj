#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "../libs/rapidxml-1.13/rapidxml.hpp"
#include "../libs/rapidxml-1.13/rapidxml_utils.hpp"

using namespace rapidxml;

void intersection(){
    

}

// Функция для определения ориентации точек a, b и c.
// Возвращает положительное значение, если точки идут по часовой стрелке,
// отрицательное значение, если против часовой стрелки, и 0, если они лежат на одной прямой.
double orientation(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Функция для проверки, находится ли точка p внутри треугольника abc.
bool isInsideTriangle(const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c, const sf::Vector2f &p) {
    double orientABP = orientation(a, b, p);
    double orientBCP = orientation(b, c, p);
    double orientCAP = orientation(c, a, p);

    // Если все ориентации имеют одинаковый знак, то точка находится внутри треугольника.
    return (orientABP >= 0 && orientBCP >= 0 && orientCAP >= 0) || (orientABP <= 0 && orientBCP <= 0 && orientCAP <= 0);
}

void TestBlood() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(500, 500), "123");
    window.setFramerateLimit(30);
    std::random_device rd;
    const int size = 30;
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
    sf::Image image1, image2, image3;
    sf::Texture texture1, texture2, texture3;
    sf::Sprite sprite1, sprite2, sprite3;

    sf::Vector2f a = {0, 0};
    sf::Vector2f b = {0, size};
    sf::Vector2f c = {size, size / 2};
    std::uniform_int_distribution<int> distribution1(0, 355);
    std::uniform_int_distribution<int> distribution2(50, 300);
    std::uniform_int_distribution<int> distribution3(0, 255);

    image1.create(size, size, sf::Color(255, 255, 255, 0));
    image2.create(size, size, sf::Color(255, 255, 255, 0));
    image3.create(size, size, sf::Color(255, 255, 255, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int tmp = distribution1(gen);
            if (((tmp < 255 && tmp > 230) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 255) {
                image1.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int tmp = distribution1(gen);
            if (((tmp < 200 && tmp > 170) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 200) {
                image2.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int tmp = distribution1(gen);
            if (((tmp < 145 && tmp > 160) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 160) {
                image3.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }

    texture1.loadFromImage(image1);
    sprite1.setTexture(texture1);
    sprite1.setPosition(0, 0);
    texture2.loadFromImage(image2);
    // sprite2.setTexture(texture2);
    // sprite2.setPosition(0, size * 1);
    texture3.loadFromImage(image3);
    // sprite3.setTexture(texture3);
    // sprite3.setPosition(0, size * 2);

    bool isActive = true;
    sf::Event e;
    int cnt = 0;
    while (isActive) {
        window.clear(sf::Color::White);
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                isActive = false;
        }
        if (cnt == 0)
            sprite1.setTexture(texture1);
        if (cnt == 1)
            sprite1.setTexture(texture2);
        if (cnt == 2) {
            sprite1.setTexture(texture3);
            cnt = -1;
        }
        window.draw(sprite1);
        ++cnt;
        window.display();
    }
}

int main() {

    TestBlood();

    return 0;
}