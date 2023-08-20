#pragma once
#include <SFML/Graphics.hpp>
#include "Obj.hpp"
#include <string>
#include <memory>

#ifndef DEBUG
#define DEBUG                                           \
    {                                                   \
        std::cout << "Line: " << __LINE__ << std::endl; \
    }
#endif // DEBUG

class Label : public Obj
{
public:
    enum Align
    {
        Center,
        Left
    };

    enum Anims {
        None,
        AppearanceDecay
    };

    Label(sf::RenderWindow *window, sf::Font &font, std::wstring text, const float x, const float y, Align align = Align::Center, const unsigned int fSize = 30, const float w = 200);
    void ChangeText(std::wstring t);
    void Draw() override;
    sf::Text &getText();
    void UpdateMaxWidth(const float w);
    void SetAnimation(Anims type);
    void Update() override;
    void DoAppearanceDecay();

private:
    void AlignToCenter();
    void AlignToLeft();

    int animOpacity;
    bool animStart = true;
    bool animStop;
    Anims animType;
    Align align;
    sf::RenderWindow *window;
    sf::Font &Geologica;
    sf::Text text;
    float maxWidth = 200;
};