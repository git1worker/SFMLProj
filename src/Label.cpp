#include "Label.hpp"
#include <iostream>

Label::Label(sf::RenderWindow *window, sf::Font& font, std::wstring str, const float x, const float y, const unsigned int fSize, const float w) 
    : window(window), Geologica(font) 
{   
    this->x = x;
    this->y = y;
    text.setString(str);
    text.setFont(Geologica);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(fSize);
    this->maxWidth = w;
    AlignToWidth();
}

sf::Text &Label::getText()
{
    return text;
}

void Label::UpdateMaxWidth(const float w)
{
    maxWidth = w;
    AlignToWidth();
}

void Label::AlignToWidth()
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
    text.setString(newStr);
    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, (text.getCharacterSize() - text.getGlobalBounds().height) + text.getGlobalBounds().height/2));
    text.setPosition(sf::Vector2f(x, y));
}

void Label::Draw()
{
    window->draw(text);
}

void Label::ChangeText(std::wstring t)
{   
    text.setString(t);
    AlignToWidth();
}