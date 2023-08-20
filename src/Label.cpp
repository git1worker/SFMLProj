#include "Label.hpp"
#include <iostream>

Label::Label(sf::RenderWindow *window, sf::Font& font, std::wstring str, const float x, const float y, Align align, const unsigned int fSize, const float w) 
    : window(window), Geologica(font), align(align)
{   
    this->x = x;
    this->y = y;
    text.setString(str);
    text.setFont(Geologica);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(fSize);
    this->maxWidth = w;
    switch (align)
    {
    case Align::Left:
        AlignToLeft();
        break;
    default:
        AlignToCenter();
        break;
    }
    
}

sf::Text &Label::getText()
{
    return text;
}

void Label::UpdateMaxWidth(const float w)
{
    maxWidth = w;
    AlignToCenter();
}

void Label::SetAnimation(Anims type)
{
    this->animType = type;
    
}

void Label::Update()
{
    switch (animType)
    {
    case Anims::AppearanceDecay:
        DoAppearanceDecay();
        break;
    
    default:
        break;
    }
}

void Label::DoAppearanceDecay(){
    if (animStart) {
        animStart = false;
        animOpacity = 0;
        animStop = false;
    }
    if (!animStop){
        //std::cout << 231 << std::endl;
        text.setFillColor(sf::Color(text.getFillColor().r, text.getFillColor().g, text.getFillColor().b, animOpacity++));
        if (animOpacity == 255) animStop = true;
    }
    else if (animStop){
        text.setFillColor(sf::Color(text.getFillColor().r, text.getFillColor().g, text.getFillColor().b, animOpacity--));
        if (animOpacity == 0) deleteIt = true;
    }
}

void Label::AlignToCenter()
{
    std::wstring newStr;
    int i = 1;
    for (auto it = text.getString().begin(); it != text.getString().end(); ++it){
        if (maxWidth > i * (text.getCharacterSize() + text.getLetterSpacing())){
            if (*it == L'\n') i = 1;
            newStr.push_back(*it);
            // DEBUG
            // std::cout << std::string(newStr.begin(), newStr.end()) << std::endl;
            // std::wcout <<  maxWidth << L' ' << i * text.getCharacterSize() << L' ' << newStr << L'\n';
            ++i;
        }
        else newStr.push_back(L'\n'), newStr.push_back(*it), i = 2;
    }
    if (!text.getString().isEmpty()){
        text.setString(newStr);
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, (text.getCharacterSize() - text.getGlobalBounds().height) + text.getGlobalBounds().height/2));
        text.setPosition(sf::Vector2f(x, y));
    }
}

void Label::AlignToLeft()
{
    std::wstring newStr;
    int i = 1;
    for (auto it = text.getString().begin(); it != text.getString().end(); ++it){
        if (maxWidth > i * (text.getCharacterSize() + text.getLetterSpacing())){
            if (*it == L'\n') i = 1;
            newStr.push_back(*it);
            // DEBUG
            // std::cout << std::string(newStr.begin(), newStr.end()) << std::endl;
            // std::wcout <<  maxWidth << L' ' << i * text.getCharacterSize() << L' ' << newStr << L'\n';
            ++i;
        }
        else newStr.push_back(L'\n'), newStr.push_back(*it), i = 2;
    }
    if (!text.getString().isEmpty()){
        text.setString(newStr);
        text.setOrigin(sf::Vector2f(0, 0));
        text.setPosition(sf::Vector2f(x, y));
    }
    
}

void Label::Draw()
{
    window->draw(text);
}

void Label::ChangeText(std::wstring t)
{   
    text.setString(t);
    switch (align)
    {
    case Align::Left:
        AlignToLeft();
        break;
    default:
        AlignToCenter();
        break;
    }
}