#include "SplashOfBlood.hpp"
#include "Gamew.hpp"
#include "Debug.hpp"

SplashOfBlood::SplashOfBlood(Gamew* gamew) {
    this->gamew = gamew;
    speed = 110;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution1(100, 355);
    std::uniform_int_distribution<int> distribution2(50, 300);
    std::uniform_int_distribution<int> distribution3(0, 255);
    const int size = 14;
    image1.create(size, size, sf::Color(255, 255, 255, 0));
    image2.create(size, size, sf::Color(255, 255, 255, 0));
    image3.create(size, size, sf::Color(255, 255, 255, 0));
    sf::Vector2f a = {0,0};
    sf::Vector2f b = {0,size};
    sf::Vector2f c = {size,size / 2};
    // Generation of random sprite of blood //
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            int tmp = distribution1(gen);
            if (((tmp < 255 && tmp > 230 ) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 255){
                image1.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            int tmp = distribution1(gen);
            if (((tmp < 200 && tmp > 170 ) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 200){
                image2.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            int tmp = distribution1(gen);
            if (((tmp < 145 && tmp > 160 ) || isInsideTriangle(a, b, c, sf::Vector2f(j, i))) && tmp >= 127 && tmp <= 160){
                image3.setPixel(j, i, sf::Color(tmp, 0, 0));
            }
        }
    }
    texture1.loadFromImage(image1);
    texture2.loadFromImage(image2);
    texture3.loadFromImage(image3);
    sprite.setOrigin(size, size / 2);
}

void SplashOfBlood::Draw() {
    if (!stop)
        gamew->window->draw(sprite);
}

void SplashOfBlood::Update() {
    if (!stop) {
        if (!animate) {
            start = std::chrono::system_clock::now();
            animate = true;
            currFrame = 1;
            sprite.setTexture(texture1, true);
        } else {
            if (std::chrono::system_clock::now() - start > std::chrono::milliseconds(speed * currFrame)) {
                ++currFrame;
                if (currFrame == 4)
                    stop = true, animate = false;
                if (currFrame == 2)
                    sprite.setTexture(texture2, true);
                else if (currFrame == 3)
                    sprite.setTexture(texture3, true);
                
            }
        }
        sprite.setPosition(pos.x + gamew->offsetRelativeCenter.x, pos.y + gamew->offsetRelativeCenter.y);
    }
    //RTDrawing(gamew->window, sprite);
}

void SplashOfBlood::StartSplash(float x, float y, sf::Vector2f direction) {
    pos.x = x;
    stop = false;
    animate = false;
    pos.y = y;
    float tg = direction.y / direction.x;
    if (direction.x > 0)
        sprite.setRotation(-(atan(tg) * 180 / 3.1415));
    else sprite.setRotation(-(atan(tg) * 180 / 3.1415) + 180);
}


double SplashOfBlood::orientation(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Функция для проверки, находится ли точка p внутри треугольника abc.
bool SplashOfBlood::isInsideTriangle(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& p) {
    double orientABP = orientation(a, b, p);
    double orientBCP = orientation(b, c, p);
    double orientCAP = orientation(c, a, p);

    // Если все ориентации имеют одинаковый знак, то точка находится внутри треугольника.
    return (orientABP >= 0 && orientBCP >= 0 && orientCAP >= 0) ||
           (orientABP <= 0 && orientBCP <= 0 && orientCAP <= 0);
}